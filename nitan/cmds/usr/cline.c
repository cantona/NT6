// cline.c 清除末尾幾行

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        int n;
        string msg;

        if (! stringp(arg) || ! sscanf(arg, "%d", n))
                n = 24;

        if (n < 1 || n > 500)
        {
                write("參數錯誤。\n");
                return 1;
        }

        msg = "";
        while (n--)
                msg += ESC "[1A" ESC "[K";

        write(msg);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : cline [<行數>]

此指令可讓你清除最後幾行文字，做什麼用？自己想吧。
HELP );
        return 1;
}