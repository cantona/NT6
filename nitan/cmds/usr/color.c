// color.c (Simba 13.sept.97)

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me)
{
        tell_object(me,MAG"★"HIY"色彩精靈向您報告"MAG"★\n\n"NOR);
        tell_object(me,
"  黑色- BLK"BLK"■■■                       BBLK"BBLK"■■■"NOR"\n"
"  紅色- RED"RED"■■■"NOR" HIR"HIR"■■■"NOR" HBRED"HBRED"■■■"NOR" BRED"BRED"■■■"NOR"\n"
"  綠色- GRN"GRN"■■■"NOR" HIG"HIG"■■■"NOR" HBGRN"HBGRN"■■■"NOR" BGRN"BGRN"■■■"NOR"\n"
"  黃色- YEL"YEL"■■■"NOR" HIY"HIY"■■■"NOR" HBYEL"HBYEL"■■■"NOR" BYEL"BYEL"■■■"NOR"\n"
"  藍色- BLU"BLU"■■■"NOR" HIB"HIB"■■■"NOR" HBBLU"HBBLU"■■■"NOR" BBLU"BBLU"■■■"NOR"\n"
"  粉色- MAG"MAG"■■■"NOR" HIM"HIM"■■■"NOR" HBMAG"HBMAG"■■■"NOR" BMAG"BMAG"■■■"NOR"\n"
"  青色- CYN"CYN"■■■"NOR" HIC"HIC"■■■"NOR" HBCYN"HBCYN"■■■"NOR" BCYN"BCYN"■■■"NOR"\n"
"  白色- WHT"WHT"■■■"NOR" HIW"HIW"■■■"NOR" HBWHT"HBWHT"■■■"NOR"\n"
"  灰色- HIK"HIK"■■■"NOR"\n");
        return 1;
}
int help(object me)
{
        write(@HELP
指令格式 : color

這個指令可以讓你知道遊戲中各種色彩的ANSI控制字元及色彩的
試樣，從而方便您選擇中意的色彩。

HELP );
        return 1;
}