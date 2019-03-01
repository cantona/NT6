#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "bingcan_duzhang"; }

string chinese_name() { return "冰蠶寒毒"; }

string update_msg_others()
{
       return HIW "$N" HIW "慘嚎一聲，臉色鐵青，全身浮現出一層寒氣，不住的顫抖。\n" NOR;
}

string update_msg_self()
{
        return HIW "你只覺極寒攻心，全身肌肉快要凍結一般。\n" NOR;
}

