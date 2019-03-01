// find.c
// By jjgod for FYTX.

#include <ansi.h>

// ENABLE_BAR 模式針對類 hell 的 MUD，它提供了 process_bar()
// 這個 simul_efun 和 attack_system(),detach_system() 這兩個
// 定義在 USER_OB 的函數，並且利用 ANSI 控制符對提示符有了一
// 些改進。開啟時定義為 1 即可。
#define ENABLE_BAR      1

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

public void search_dir(object me, string file, string dir, int raw);
public void search_in_file(object me, string info, string file);
public string *search_file(string file, string *flist, object me, int raw);
public string *deep_file_list(string dir);
string itoa(int i) { return sprintf("%d", i); }

int main(object me, string arg)
{
        string file, dir, flag;
        int raw;

        // 權限檢查，需要安全系統支持
        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if (! arg)
                return notify_fail("指令格式：find <文件名|內容> in <目錄名|文件名> [-c]\n");

        if (sscanf(arg, "%s in %s %s", file, dir, flag) != 3)
        {
                if (sscanf(arg, "%s in %s", file, dir) != 2)
                        notify_fail("指令格式：find <文件名|內容> in <目錄名|文件名> [-c]\n");
        }

        // 如果是查找包含內容模式
        if (flag == "-c") raw = 1;

        dir=resolve_path(query("cwd", me),dir);

        seteuid(getuid(me));

        // 如果是在文件中查找模式
        if (file_size(dir) >= 0)
        {
                search_in_file(me, file, dir);
                return 1;
        }

        if (file_size(dir) == -2 && dir[strlen(dir) - 1] != '/') dir += "/";
        if (file_size(dir) != -2)
                return notify_fail(dir + " 並不是一個目錄。\n");

        // 給一點提示，因為玩家可能會過于遲滯
        message_system("系統進行數據處理中，請耐心等候...");

#if ENABLE_BAR
        write(HIR "\n現在系統正在搜索 " + dir + " 目錄，稍後匯報。\n\n" NOR
              HIW "進度：" + process_bar(0) + "\n");
        if (me)
        {
                me->attach_system();
                me->write_prompt();
        }
#endif
        search_dir(me, file, dir, raw);
        return 1;
}

void search_dir(object me, string file, string dir, int raw)
{
        int i;
        string *flist, *result;
        string info, file_info, size;

        // 獲得所有的深層目錄文件列表
        flist = deep_file_list(dir);

        if (! arrayp(flist) || ! sizeof(flist))
        {
                message_system("系統數據處理完畢，請繼續遊戲。\n" ESC + "[K");
                info = HIR "文件搜索完畢：\n\n" NOR ESC + "[K"
                       HIR "目錄 " + dir + " 下並沒有可供查找的文件。" NOR;

                message("system", info, me);
#if ENABLE_BAR
                me->detach_system();
#endif
                return;
        }

        result = search_file(file, flist, me, raw);

#if ENABLE_BAR
        me->detach_system();
#endif

        message_system("系統數據處理完畢，請繼續遊戲。\n" ESC + "[K");

        if (! sizeof(result))
                info = HIR "文件搜索完畢：\n" + ESC + "[K" + "\n" NOR ESC + "[K"
                       HIR "目錄 " + dir + " 下沒有找到任何符合要求的文件。\n" NOR
                       ESC + "[K";

        else
        {
                file_info = "";
                for (i = 0; i < sizeof(result); i++)
                {
                        if (eval_cost() < 10000) set_eval_limit(0);
                        size = itoa(file_size(result[i]) / 1000);
                        file_info += sprintf(CYN "%-45s " WHT "%4s " CYN " %s\n",
                                             result[i],
                                             (size == "0" ? itoa(file_size(result[i])) + "b" : size + "k"),
                                             CHINESE_D->chinese_time(9, ctime(stat(result[i])[1])), );
                }

                info = HIR "文件搜索完畢：\n" + ESC + "[K" + "\n" NOR ESC + "[K" +
                       file_info + NOR + ESC + "[K"
                       HIR "\n一共找到 " + sizeof(result) + " 個文件。" + ESC + "[K" + NOR
                       ESC + "[K\n" + ESC + "[K";
        }

        if (me)
                me->start_more(info);
//              message("system", info, me);
}

string *deep_file_list(string dir)
{
        int i;
        string *flist, *result = ({ });
        string file;

        flist = get_dir(dir);

        for (i = 0; i < sizeof(flist); i++)
        {
                if (eval_cost() < 10000) set_eval_limit(0);
                file = dir + flist[i];

                if (file_size(file + "/") == -2)
                        result += deep_file_list(file + "/");
                else
                        result += ({ file });
        }

        return result;
}

string *search_file(string file, string *flist, object me, int raw)
{
        int i, j;
        string *result = ({ });
        string file_info;

        for (i = 0; i < sizeof(flist); i++)
        {
                if (eval_cost() < 10000) set_eval_limit(0);
#if ENABLE_BAR
                message("system", NOR ESC + "[1A" + ESC + "[256D"
                                  HIG "進度：" + process_bar((i + 1) * 100 / sizeof(flist)) +
                                  "\n" + ESC + "[K", me);
#endif
                if (raw == 0)
                {
                        j = strsrch(flist[i], "/", -1);
                        file_info = flist[i][j..(sizeof(flist[i]) - 1)];

                        if (file_info == file)
                        {
                                result += ({ flist[i] });
                                continue;
                        }
                        if (strsrch(file_info, file) > -1)
                        {
                                result += ({ flist[i] });
                                continue;
                        }
                }
                else
                {
                        // 如果文件本身都沒有這個要找的字符串長
                        if (file_size(flist[i]) < strlen(file))
                                continue;

                        if (catch(read_file(flist[i])))
                                log_file("readfile", sprintf("%s\n", flist[i]));
                        if (! read_file(flist[i]))
                                continue;

                        if (strsrch(read_file(flist[i]), file) > -1)
                        {
                                result += ({ flist[i] });
                                continue;
                        }
                }
        }
        return result;
}

void search_in_file(object me, string word, string file)
{
        string text, info;
        string *lines;
        int line, num, i, count = 0;

        seteuid(getuid(me));
        if (catch(read_file(file)))
                log_file("readfile", sprintf("%s\n", file));
        if (! text = read_file(file))
        {
                write(HIR "\n文件 " + file + " 打開失敗，可能是因為文件過大。\n" NOR);
                return;
        }

        if (strsrch(text, word) == -1)
        {
                write(HIR "\n文件 " + file + " 內部並無包含“" HIW + word +
                      HIR "”字符串。\n" NOR);
                return;
        }

        lines = explode(text, "\n");
        info = HIR "正在文件 " + file + " 中查找包含 " + word + "\n字符串的內容：\n\n" NOR;

        line = sizeof(lines);
        for (i = 0; i < line; i++)
        {
                if (eval_cost() < 10000) set_eval_limit(0);
                num = strsrch(lines[i], word);

                if (num > -1)
                {
                        info += WHT "在第 " + (i + 1) + " 行的第 " + (num + 1) + " 字節處"
                                "找到指定字符。\n" NOR;

                        info += CYN "............\n" NOR;
                        info += (i - 1) >= 0 ? CYN + lines[i - 1] + "\n" + NOR : "";
                        info += CYN + replace_string(lines[i], word, WHT + word + CYN) + "\n" + NOR;
                        info += (i + 1) < line ? CYN + lines[i + 1] + "\n" + NOR : "";
                        info += CYN "............\n\n" NOR;

                        count++;
                }
        }
        info += HIR "查詢完畢，一共找到 " + count + " 個符合的內容。" NOR;

        me->start_more(info);
        return;
}

int help(object me)
{
        write(@HELP
指令格式: find <文件名|內容> in <目錄名|文件名> [-c]

查找目錄及其子目錄下所有包含指定文件名的文件和目錄。查找結果返
回的格式為：<文件名> <文件大小> <上一次修改時間>。
如果加上了 -c 參數則表示查找在指定目錄下包含指定內容的文件。
如果指定的位置是一個文件名，則表示在那個文件中查找包含指定內容
的行。
HELP );
        return 1;
}