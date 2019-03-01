// unset.c
#include <ansi.h>

inherit F_CLEAN_UP;

int help();

int main(object me, string arg)
{
        if( !arg || arg=="" ) return help();

        delete("env/"+arg, me);
        if (arg == "show_map")
                write(ESC+"[r"+TOBOT(50));
        write("Ok.\n");
        return 1;
}

int help()
{
        write(@TEXT
指令格式：unset <變數名>

這個指令讓你刪除環境變數的設定。

修改變數設定請用 unset 指令。
TEXT
        );
        return 1;
}