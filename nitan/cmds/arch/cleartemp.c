// cleartemp.c
// created by doing

#include <ansi.h>
#include <localtime.h>

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
        string flogin;
        string fuser;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if (! arg)
                return help(me);

        seteuid(getuid());
        arg = arg[0..0] + "/" + arg + __SAVE_EXTENSION__;
        flogin = TEMP_DIR + "login/" + arg;
        fuser  = TEMP_DIR + "user/"  + arg;

        if (file_size(flogin) < 0 &&
            file_size(fuser) < 0)
        {
                write("這個玩家在暫存區中沒有臨時檔案。\n");
                return 1;
        }

        rm(flogin);
        rm(fuser);
        if (file_size(flogin) >= 0 ||
            file_size(fuser) >= 0)
        {
                write("清除暫存區中玩家(" + arg + ")的文件失敗了。");
                return 1;
        }

        write("成功的清除暫存中玩家(" + arg + ")的檔案。\n");
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式：cleartemp <玩家ID>

這是清除暫存區中的玩家臨時檔案的命令，這些臨時檔案一般是使用 restore
命令從備份區恢復玩家數據時產生的。

相關指令：restore
HELP );
        return 1;
}