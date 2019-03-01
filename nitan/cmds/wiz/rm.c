// rm.c
// created by doing

#include <ansi.h>
 
inherit F_CLEAN_UP;
 
protected int rm_item(string file, int rm_dir, object me);
int rm_dir(string dir);
int help(object me);

int main(object me, string arg)
{
        string file;
        string dir;
        string grant;
        int rm_dir;
        int count;
        string path;
        mixed flist;
        int i;
 
        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        seteuid(geteuid(me));
 
        if (! arg)
        {
                help(me);
                return 1;
        }

        if (sscanf(arg, "-R %s", dir) == 1)
        {
                if (me && ! is_root(me))
                {
                        write("只有管理員才能使用 -R 參數。\n");
                        return 1;
                }

                if (strsrch(dir, "*") != -1)
                {
                        write("為了安全起見，使用 -R 的參數的時候不能使用通配符。\n");
                        return 1;
                }

                if (dir == "/")
                {
                        write("你不能刪除根目錄。\n");
                        return 1;
                }

                rm_dir = 1;
        } else
        {
                dir = arg;
                rm_dir = 0;
        }

        file=resolve_path(query("cwd", me),dir);
        if (! me->is_admin()) 
        {
                grant = SECURITY_D->query_site_privilege("edit");
                if( !grant && !sscanf(file, "/u/%*s") )
                        return notify_fail("你只能刪除你自己的目錄下文件。\n");
                        
                if( grant != "all" && !sscanf(file, "/%s/%*s", grant) )
                        return notify_fail("你只能刪除你自己目錄下以及" + grant + "目錄下文件。\n");
        }
        flist = get_dir(file);
        if (arrayp(flist)) flist -= ({ ".", ".." });
        if (! arrayp(flist) || ! sizeof(flist))
        {
                write("沒有這個文件。\n");
                return 1;
        }

        path = "";
        while ((i = strsrch(file, "/")) != -1)
        {
                path += file[0..i];
                file = file[i + 1..<1];
        }

        if (rm_dir)
                message_system(HIR "刪除目錄中，請稍候..." NOR),

        count = 0;
        for (i = 0; i < sizeof(flist); i++)
        {
                count += rm_item(path + flist[i], rm_dir, me);
        }

        if (count)
                write(HIY "總共有" + count + "個文件被成功刪除。\n" NOR);
        else
                write("沒有刪除任何文件。\n");
        return 1;
}

protected int rm_item(string file, int rm_dir, object me)
{
        switch (file_size(file))
        {
        case -1:
                write("沒有這個文件。\n");
                return 0;

        case -2:
                if (rm_dir)
                        return rm_dir(file);

                if (rmdir(file))
                        write("成功的刪除了目錄(" + file + ").\n");
                else
                        write("你沒有刪除該目錄的權限或者試圖刪除一個"
                              "非空的目錄(" + file + ")。\n");
                return 0;
                
        default:
                SECURITY_D->backup_file(file);
                if (rm(file))
                        return 1;

                if (! SECURITY_D->valid_read(file, me, "ls"))
                        return 0;

                write("你沒有刪除(" + file + ")的權限。\n");
                return 1;
        }
}
 
int rm_dir(string dir)
{
        mixed *file;
        int count;
        int i;

        if (! is_root(previous_object()))
                return 0;

        count = 0;
        if (dir[strlen(dir) - 1] != '/') dir += "/";
        file = get_dir(dir, -1);

        i = sizeof(file);
        while (i--)
        {
                reset_eval_cost();
                if (file[i][1] != -2)
                        if (rm(dir + file[i][0]))
                                count++;
        }

        i = sizeof(file);
        while (i--)
        {
                reset_eval_cost();
                if (file[i][1] == -2)
                        count += rm_dir(dir + file[i][0]);
        }

        write (HIC "刪除目錄(" + dir + ")。\n" NOR);
        rmdir(dir);
        return count;
}

int help(object me)
{
        write(@HELP
指令格式 : rm [-R] 檔案名
 
此指令可讓你刪除某個檔案或目錄。如果使用了-R參數，可以刪除非空的目
錄，使用該參數務必要小心，以免刪除錯路徑。

see also: cp, mv
HELP );
        return 1;
}
