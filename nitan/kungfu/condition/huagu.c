// huagu.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "huagu"; }

string chinese_name() { return "化骨掌傷"; }

string update_msg_others()
{
       return HIC "$N" HIC "的身子突然晃了兩晃，幾乎跌倒。\n" NOR;
}

string update_msg_self()
{
        return HIR "忽然渾身一陣劇痛，你中的化骨綿掌毒發了！\n" NOR;
}

string die_reason()
{
        return "筋斷骨碎，死的慘不堪言";
}
