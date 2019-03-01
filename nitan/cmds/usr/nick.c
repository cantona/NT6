// nick.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        if (! arg)
                return notify_fail("你要替自己取什麼綽號？\n");

        if (arg == "none")
        {
                delete("nickname", me);
                write("你的綽號取消了。\n");
                return 1;
        }

        if (strlen(arg) > 80)
                return notify_fail("你的綽號佔用的資源過多，請重新設置。\n");

        arg = replace_string(arg, "$BLK$", BLK);
        arg = replace_string(arg, "$RED$", RED);
        arg = replace_string(arg, "$GRN$", GRN);
        arg = replace_string(arg, "$YEL$", YEL);
        arg = replace_string(arg, "$BLU$", BLU);
        arg = replace_string(arg, "$MAG$", MAG);
        arg = replace_string(arg, "$CYN$", CYN);
        arg = replace_string(arg, "$WHT$", WHT);
        arg = replace_string(arg, "$HIR$", HIR);
        arg = replace_string(arg, "$HIG$", HIG);
        arg = replace_string(arg, "$HIY$", HIY);
        arg = replace_string(arg, "$HIB$", HIB);
        arg = replace_string(arg, "$HIM$", HIM);
        arg = replace_string(arg, "$HIC$", HIC);
        arg = replace_string(arg, "$HIW$", HIW);
        arg = replace_string(arg, "$NOR$", NOR);
        arg = replace_string(arg, "\"", "");

        if (strlen(filter_color(arg)) > 30)
                return notify_fail("你的綽號太長了，想一個短一點的、響亮一點的。\n");

        set("nickname", arg+NOR, me);
        write("你取好了綽號。\n");
        return 1;
}
int help(object me)
{
        write(@HELP
指令格式 : nick <外號, 綽號> | none
 
這個指令可以讓你為自己取一個響亮的名號或頭
銜，你如果希望在綽號中使用 ANSI 的控制字元
改變顏色，可以用以下的控制字串：

 $BLK$ - 黑　色            $NOR$ - 正常色
 $RED$ - [31m紅　色[2;37;0m            $HIR$ - [1;31m亮紅色[2;37;0m
 $GRN$ - 綠　色            $HIG$ - [1;32m亮綠色[2;37;0m
 $YEL$ - [33m土黃色[2;37;0m            $HIY$ - [1;33m黃　色[2;37;0m
 $BLU$ - [34m深藍色[2;37;0m            $HIB$ - [1;34m藍　色[2;37;0m
 $MAG$ - [35m淺紫色[2;37;0m            $HIM$ - [1;35m粉紅色[2;37;0m
 $CYN$ - [36m藍綠色[2;37;0m            $HIC$ - [1;36m天青色[2;37;0m
 $WHT$ - [37m淺灰色[2;37;0m            $HIW$ - [1;37m白　色[2;37;0m
 
禁止在 nick 中使用 $BLINK$ - [5m[1;37m字[2;37;0m[5m[1;36m符[2;37;0m[5m[35m閃[2;37;0m[5m[1;33m爍[2;37;0m
其中系統自動會在字串尾端加一個 $NOR$。

HELP );
        return 1;
}