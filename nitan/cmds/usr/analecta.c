// analecta.c
// Create by jjgod. 2002/01/27.
// Optimized by jjgod. 2002/12/14.
// Optimized by jjgod. 2003/01/01.

#include <ansi.h>
#include <mudlib.h>
#include <localtime.h>
#include <analecta.h>

inherit F_CLEAN_UP;

int    help(object me);
string list_analectas(mapping *analectas, int year, object me);
string read_analecta(int year, mapping analecta, int i, object me);

int main(object me, string arg)
{
        string info, name, id, *all_analecta, dir;
        int year, i;
        object board;
        mapping all_note, analecta;
        mapping *analectas;

        MYGIFT_D->check_mygift(me, "newbie_mygift/wenxuan");   
        year = localtime(time())[LT_YEAR];
        analectas = ANALECTA_D->query_year_analecta(year);

        info = HIC + LOCAL_MUD_NAME() + "(" + HIW + upper_case(INTERMUD_MUD_NAME) + 
               HIC + ")文章選集：\n" NOR WHT "──────────────────"
               "──────────────────\n" NOR;

        // 閲讀最新文選
        if (arg == "new" || arg && sscanf(arg, "new %d", year))
        {
                analectas = ANALECTA_D->query_year_analecta(year);
                if (! arrayp(analectas) || ! sizeof(analectas))
                        info += CYN " 現在 " WHT + year + CYN " 沒有任何新的文選"
                                "供你閲讀。\n";
                else
                {
                        i=query("analecta_last_read/"+year, me);
                        analectas = sort_array(analectas, (: sort_analectas :));
                        analectas = filter_array(analectas, (: filter_analectas :), i);
                        if (! sizeof(analectas))
                                info += CYN " 現在 " WHT + year + CYN " 年沒有任何"
                                        "新的文選供你閲讀。\n";
                        else
                                info += read_analecta(year, analectas[0],
                                                      member_array(analectas[0], analectas) + 1,
                                                      me);
                }
        }
        else
        // 添加文選
        if (arg && sscanf(arg, "add %d from %s", i, name) == 2)
        {
                if (! objectp(board = present(name, environment(me))))
                        info += CYN " 這裏沒有 " WHT + name + 
                                CYN " 這塊留言板。\n" NOR;
                else
                if (! SECURITY_D->valid_grant(me, "(immortal)") 
                 && query("id", me) != query("banzhu", board) )
                        info += CYN " 你尚無權力添加文選。\n" NOR;
                else
                {
                        all_note=query("notes", board);
                        if (! arrayp(all_note) || i < 1 || i > sizeof(all_note))
                                info += CYN " 沒有這張留言。\n" NOR;
                        else
                        {
                                i--;
                                // sscanf(all_note[i]["author"], "%s-%s", name, id);
                                analecta = ([ ]);
                                analecta["subject"] = all_note[i]["title"];
                                analecta["author_name"] = all_note[i]["author"];
                                analecta["author_id"] = all_note[i]["owner"];
                                analecta["time"] = all_note[i]["time"];
                                analecta["content"] = all_note[i]["msg"];
                                analecta["board"] = board->name();

                                ANALECTA_D->add_analecta(year, analecta);
                                info += CYN " 已經成功的添加了" + board->name() +
                                        "的 " WHT + (i + 1) + CYN " 號留言進入"
                                        "本年度文選。\n" NOR;
                        }
                }
        }
        // 刪除文選
        else
        if (arg && sscanf(arg, "del %d %d", year, i) == 2)
        {
                if (! wizardp(me))
                        info += CYN " 你尚無權力刪除文選。\n" NOR;
                else
                if (! ANALECTA_D->delete_analecta(year, i))
                        info += CYN " 沒有 " WHT + year + CYN " 這個年度的文選"
                                "或該年度沒有 " WHT + i + CYN " 這個序號的文選"
                                "。\n" NOR;
                else
                        info += CYN " 年度 " WHT + year + CYN " 編號 " WHT + i +
                                CYN " 的文選已經被成功刪除。\n" NOR;
        }
        else
        // 轉換舊版本文選
        if (arg && sscanf(arg, "convert %s", dir))
        {
                if (! wizardp(me))
                        return 0;

                if (file_size(dir) != -2)
                        info += CYN " 沒有 " WHT + dir + CYN " 這個目錄可供轉換"
                                "。\n";
                else
                {
                        string subject, board_name;
                        int time;
                        int j = 0;

                        all_analecta = get_dir(dir);
                        for (i = 0; i < sizeof(all_analecta); i++)
                        {
                                if (sscanf(all_analecta[i], "%s-%s-%s-%d-%s",
                                    subject, name, id, time, board_name) != 5)
                                {
                                        write(all_analecta[i] + " parse error.\n");
                                        continue;
                                }

                                analecta = ([ ]);
                                analecta["subject"] = subject;
                                analecta["author_name"] = name;
                                analecta["author_id"] = id;
                                analecta["time"] = time;
                                analecta["board"] = board_name;
                                analecta["content"] = read_file(dir + all_analecta[i]);

                                year = localtime(time)[LT_YEAR];
                                ANALECTA_D->add_analecta(year, analecta);
                                rm(dir + all_analecta[i]);
                                j++;
                        }
                        info += CYN " 目錄 " WHT + dir + CYN " 下的舊版本文選數"
                                "據已被成功轉換了 " WHT + j + CYN " 個。\n" NOR;
                }
        }
        else
        // 列表
        if (! arg && sizeof(analectas))
        {
                info += CYN "年度 " WHT + year + CYN " 的文選有：\n\n" NOR;
                info += list_analectas(analectas, year, me);
        }
        // 閲讀指定年份的文章
        else
        if (arg && sscanf(arg, "%d %d", year, i) == 2)
        {
                analectas = ANALECTA_D->query_year_analecta(year);
                if (! arrayp(analectas) || ! sizeof(analectas))
                        info += CYN " 沒有 " WHT + year + CYN " 這個年"
                                "度的文選。\n" NOR;
                else
                if (sizeof(analectas) < i || i < 1)
                        info += CYN " 年度 " WHT + year + CYN " 沒有 "
                                WHT + i + CYN " 這個序號的文選。\n" NOR;

                else
                {
                        analectas = sort_array(analectas, (: sort_analectas :));
                        info += read_analecta(year, analectas[i - 1], i, me);
                }
        }
        // 閲讀本年度文章或者列出其他年度文章
        else
        if (arg && sscanf(arg, "%d", i))
        {
                if (i < 1) info += CYN " 沒有 " WHT + i + CYN " 這個編"
                                   "號的文選。\n" NOR;
                else
                {
                        year = localtime(time())[LT_YEAR];
                        analectas = ANALECTA_D->query_year_analecta(i);

                        if (arrayp(analectas) && sizeof(analectas))
                        {
                                info += CYN "年度 " WHT + i + CYN " 的文選有："
                                        "\n\n" NOR;
                                info += list_analectas(analectas, i, me);
                        }
                        else
                        {
                                if (arrayp(analectas = ANALECTA_D->query_year_analecta(year)) &&
                                    sizeof(analectas) && sizeof(analectas) >= i)
                                {
                                        analectas = sort_array(analectas, (: sort_analectas :));
                                        info += read_analecta(year, analectas[i - 1], i, me);
                                }

                                else info += CYN " 沒有 " WHT + i + CYN " 這個年度或者"
                                             "本年這個序號的文選。\n" NOR;
                        }
                }
        }
        // 列出有文選的年份
        else
        if (! arrayp(analectas) || ! sizeof(analectas) || arg == "years")
        {
                all_analecta = keys(ANALECTA_D->query_analecta_list());
                // all_analecta -= ({ sprintf("%d", year) });

                if (! sizeof(all_analecta))
                        info += CYN " 現在還沒有任何文章被收集。\n" NOR;
                else
                {
                        info += sort_string(CYN " 現在有 " WHT +
                                            implode(all_analecta, CYN "、" WHT) +
                                            CYN " 這 " WHT + sizeof(all_analecta) +
                                            CYN " 年的文選供閲讀。\n" NOR, 86);
                }
        }
        else return help(me);

        info += NOR WHT "\n───────────────────────────────"
                "─────" NOR;
        me->start_more(info);
        return 1;
}

// 列出文選標題
string list_analectas(mapping *analectas, int year, object me)
{
        int i, last;
        mapping analecta;
        string info, is_new;

        info = "";
        last=query("analecta_last_read/"+year, me);

        analectas = sort_array(analectas, (: sort_analectas :));
        for (i = 0; i < sizeof(analectas); i++)
        {
                analecta = analectas[i];
                is_new = analecta["add_time"] > last ? HIY : "";
                info += sprintf(CYN "%s[" NOR WHT "%3d" CYN "%s]" NOR
                                CYN "  %-30s  " WHT "%20s [" CYN "%s"
                                //WHT "| " CYN "%s" WHT " ]\n",
                                WHT "]\n",
                                is_new, i + 1, is_new, analecta["subject"],
                                analecta["author_name"] + "(" + analecta["author_id"] + ")",
                                //TIME_D->replace_ctime(analecta["time"])[0..9], analecta["board"]);
                                TIME_D->replace_ctime(analecta["time"])[0..9]);
        }
        return info;
}

// 閲讀文選
string read_analecta(int year, mapping analecta, int i, object me)
{
        string info;
        string content;

        info = sprintf(CYN "[" WHT "%3d" CYN "]  %-30s  "
                       WHT "%20s [" CYN "%s" WHT "]\n\n",
                       i, analecta["subject"],
                       analecta["author_name"] + "(" + analecta["author_id"] + ")",
                       TIME_D->replace_ctime(analecta["time"])[0..9]);

        // 文件內容通過 read_file 獲得
        content = read_file(analecta["file"], HEAD_LINES + 1,
                            analecta["lines"] - HEAD_LINES);

        if (! stringp(content) ||
            content == "")
                info += CYN "此文無任何內容。\n" NOR;
        else
                info += CYN + content + NOR;

        if( analecta["add_time"]>query("analecta_last_read/"+year, me) )
                set("analecta_last_read/"+year, analecta["add_time"], me);

        return info;
}

int help(object me)
{
        write(@HELP
指令格式 : analecta [ [ 年度 ] <序號> ] |
                    [ add <留言序號> [ from <留言板> ] ] |
                    [ del <年度> <序號> ] |
                    [ new [ 年度 ] ] |
                    [ convert <目錄> ] |
                    [ years ]

本指令提供文選的閲讀、增加和刪除。閲讀時，除本年文選不需要
指定年度外，其他的都要指定年度。 比如閲讀 2000 年第 3 號文
選，即輸入 analecta 2000 3。 使用 new 參數可以閲讀你尚未閲
讀的新文選。使用 years 參數可以列出目前有文選的年度。

巫師可以使用 new 參數來添加文選，del 參數來刪除文選。 刪除
文選需要指定年度和序號，添加文選則必須指定所在房間的留言板
ID，如：
    客棧留言板(board) [ 4 張留言 ]
使用 analecta add 1 from board，就可以把客棧留言板的第一號
留言添加到本年度文選中。

可以使用 convert參數將指定目錄下所有的舊版本文選數據轉換成
新版本的數據。
HELP);
    return 1;
}
