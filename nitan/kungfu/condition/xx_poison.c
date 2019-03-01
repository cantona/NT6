// xx_poison.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "xx_poison"; }

string chinese_name() { return "星宿掌毒"; }

string update_msg_others()
{
       return HIG "$N" HIG "的身子突然晃了兩晃，牙關格格地響了起來。" NOR;
}

string update_msg_self()
{
        return HIB "忽然一陣刺骨的奇寒襲來，你中的星宿掌毒發作了！\n" NOR;
}
