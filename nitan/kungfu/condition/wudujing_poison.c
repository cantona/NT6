#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "wudujing_poison"; }

string chinese_name() { return "五毒阱"; }

string update_msg_others()
{
       return HIW "$N胸口一熱，血氣上湧，幾欲昏倒。\n" NOR;
}

string update_msg_self()
{
        return HIM "只感到胸口一熱，血氣猛地上湧，幾欲昏倒！\n" NOR;
}

int jing_damage(object me, mapping cnd)
{
        return cnd["level"] / 20;
}

int qi_damage(object me, mapping cnd)
{
        return cnd["level"] / 20;
}

