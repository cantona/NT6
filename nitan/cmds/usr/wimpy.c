// wimpy.c

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
        int wmp;

        if( !arg ) {
                write("你現在的當「氣」低於"+query("env/wimpy", me )
                        + "% 時就會嘗試逃跑。\n");
                return 1;
        }
        if( sscanf(arg, "%d", wmp)!=1 || wmp < 0 || wmp > 80)
                return help(me);

        set("env/wimpy", wmp, me);
        write("Ok.\n");
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式： wimpy [<逃跑時「氣」的百分比>]

這個指令讓你設定當「氣」剩下百分之多少時，要開始「轉進」。
HELP
        );
        return 1;
}
