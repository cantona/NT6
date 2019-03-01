// fcrypt.c

#include <ansi.h>

inherit F_CLEAN_UP;

int build_path(string arg);

int main(object me, string arg)
{
        string affix;

        if (! me->is_admin())
                return 0;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if (! arg)
                return notify_fail("請輸入路徑名和文件名。\n");

        arg=resolve_path(query("cwd", me),arg);
        switch (file_size(arg))
        {
        case -1:
                return notify_fail("沒有這個文件或是路徑。\n");
        case -2:
                if (arg[strlen(arg) - 1] != '/') arg += "/";
                write("為 " + build_path(arg) + " 個文件增加了鑒別ID。\n");
                return 1;
        }

        if (strlen(arg) < 2)
                return notify_fail("這個文件沒有必要增加鑒別ID。\n");

        affix = arg[strlen(arg) - 2..<1];
        if (affix != ".c" && affix != ".h")
                return notify_fail("這個文件沒有必要增加鑒別ID。\n");

        if (VERSION_D->append_sn(arg) == 1)
        {
                write("成功的增加了鑒別ID。\n");
                return 1;
        }

        write("增加鑒別ID失敗了。\n");
        return 1;
}

int build_path(string path)
{
        string affix;
        mixed file;
        int count;
        int i;

        file = get_dir(path, -1);

        count = 0;
        i = sizeof(file);
        while (i--)
        {
                reset_eval_cost();
                if (file[i][1] != -2)
                {
                        affix = file[i][0][strlen(file[i][0]) - 2..<1];
                        if (affix != ".c" && affix != ".h")
                                continue;

                        switch (VERSION_D->append_sn(path + file[i][0]))
                        {
                        case 1:
                                count++;
                                write("Add file: " + file[i][0] + "\n");
                                break;

                        case 0:
                                write(HIR "Bad file: " + file[i][0] + "\n" NOR);
                                break;
                        }
                }
        }

        i = sizeof(file);
        while (i--)
        {
                reset_eval_cost();
                if (file[i][1] == -2)
                        count += build_path(path + file[i][0] + "/");
        }

        return count;
}

int help(object me)
{
        write(@HELP
指令格式 : fcrypt <目錄名> | <文件名>

利用此一指令可以為某一個文件或是某一個目錄下的所有源文件增加
數據完整性ID。

HELP
    );
    return 1;
}