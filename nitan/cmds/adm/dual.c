// this file does nothing if no shell's enabled.
// dual.c

int help(object me);

int main(object me, string arg)
{
        int flag;
        
        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if( !me->is_admin() )
                return notify_fail("你不能使用該命令。\n"); 

        if (! arg) return help(me);

        flag=query("env/dual_type", me);

        if (flag)
                return (int)me->evaluate_shell(arg, flag);

        printf("%O\n", me->evaluate_shell(arg, 0));

        return 1;

}

int help(object me)
{
        write(@HELP
指令格式 : dual [detail]

這個指令可以執行一段單獨的LPC代碼。
可以使用var命令定義的私有變量。

如果該段代碼沒有返回值，或者需要使用一個組合的代碼段。
必須設置環境變量 dual_type

與Unix相同，您也可以使用 ` 符號的內嵌命令格式，
（需要設置 use_shell 環境變量）
但是該代碼必須有返回值。
例如chatIam`me->short()`,query("short", at`here)`
query("short", short(, 會先計算出me)和here)的值，然後再替換命令。
query("exits", query("exits", 又：`here)[random(here))]`
會隨機的選擇當前房間的一個出口行走。

HELP
        );
        return 1;
}

