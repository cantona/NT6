// updateall.c
// by Doing

#include <ansi.h>

inherit F_CLEAN_UP;

int update_dir(object me, string dir, int continueable, int *total);
int update_file(object me, string file);

int main(object me, string arg)
{
        string dir;
        int continueable;
        int *total = ({0});

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        seteuid(geteuid(me));

        continueable = 0;
        if (! arg || sscanf(arg, "%s %d", dir, continueable) != 2)
                dir = arg;

        if (! dir)
        {
                dir=query("cwd", me);
                if (! dir)
                        return notify_fail("你要重新編譯那個路徑下檔案？\n");
        } else
        {
                dir=resolve_path(query("cwd", me),dir);
        }
        if (dir[strlen(dir) - 1] != '/')
                dir += "/";

        if (file_size(dir) != -2)
                return notify_fail("沒有" + dir + "這個路徑。\n");

        set("cwd", dir, me);

        message_system("整理批量檔案中，請稍候...");
        if (! update_dir(me, dir, continueable, total))
        {
                write(HIR "編譯遇到錯誤中止。\n" NOR);
        }

        if (total[0] > 0)
                write(HIC "總共有" + HIW + total[0] + HIC "個檔案被成功編譯！\n" NOR);
        else
                write(HIC "沒有編譯任何檔案。\n" NOR);

        return 1;
}

int update_dir(object me, string dir, int continueable, int *total)
{
        int i;
        int l;
        int filecount, compcount;
        mixed *file;
        string filename;

        if (! is_root(previous_object()))
                return 0;

        file = get_dir(dir, -1);
        if (! sizeof(file))
        {
                if (file_size(dir) == -2)
                        write(dir + "這個目錄是空的。\n");
                else
                        write("沒有" + dir + "這個目錄。\n");
                return 1;
        }

        write (HIY "開始編譯目錄" + dir + "下面的所有文件。\n" NOR);
        i = sizeof(file);
        compcount = 0;
        filecount = 0;
        while (i--)
        {
                reset_eval_cost();
                if (file[i][1] != -2)
                {
                        filecount++;
                        filename = file[i][0];
                        l = strlen(filename);
                        if (filename[l - 1] != 'c' || filename[l - 2] != '.')
                                continue;

                        if (! update_file(me, dir + filename) &&
                            ! continueable)
                                return 0;

                        compcount++;
                        total[0]++;
                        if ((compcount % 70) == 0)
                                write("\n");
                }

                // continue to compile next file
        }
        write(HIC "\n整理了目錄" + dir + "下的" + HIW + filecount + HIC +
              "個文件，編譯了其中" + HIW + compcount + HIC + "個檔案。\n" NOR );

        i = sizeof(file);
        while (i--)
        {
                reset_eval_cost();
                if (file[i][1] == -2)
                {
                        file[i][0] += "/";
                        write("\n");
                        if (! update_dir(me, dir + file[i][0], continueable, total) &&
                            ! continueable)
                                return 0;
                }
        }
        return 1;
}

int update_file(object me, string file)
{
        object obj;
        object *inv;
        string err;
        int i;

        if (file == "/cmds/adm/updateall.c")
                // Don't re-compile the updateall.c
                return 1;

        write (".");
        if (obj = find_object(file))
        {
                if (obj == environment(me))
                {
                        if (file_name(obj) == VOID_OB)
                                return notify_fail("\n你不能在 VOID_OB 裏重新編譯 VOID_OB。\n");

                        inv = all_inventory(obj);
                        i = sizeof(inv);
                        while(i--)
                        {
                                if (userp(inv[i])) inv[i]->move(VOID_OB, 1);
                                else inv[i] = 0;
                        }
                }
                destruct(obj);
        }

        if (obj) return notify_fail("\n無法清除舊程式碼。\n");

        err = catch( call_other(file, "???") );
        if (err)
        {
                printf( "\n發生錯誤：\n%s\n", err );
                return 0;
        } else
        {
                if ((i = sizeof(inv)) && (obj = find_object(file)))
                {
                        while(i--)
                                if (inv[i] && userp(inv[i])) inv[i]->move(obj, 1);
                }
        }

        return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : updateall <路徑名> [1]
 
這個指令可以更新某個路徑下的全部檔案, 並將新檔的內容載入記
憶體內. 如果後面尾隨標誌1， 則編譯遇到錯誤時將不會中止。
HELP
    );
    return 1;
}