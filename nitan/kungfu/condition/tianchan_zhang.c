#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "tianchan_zhang"; }

string chinese_name() { return "蟾蠱毒"; }

string update_msg_others()
{
       return HIB "只見$N" HIB "蟾蠱毒氣上湧，面上竟浮現出一層黑氣，不住的顫抖。\n" NOR;
}

string update_msg_self()
{
        return HIB "你只覺蟾蠱毒攻心，頭暈目眩，一陣說不出的惡心。\n" NOR;
}