#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "lb_poison"; }

string chinese_name() { return "綠波劇毒"; }

string update_msg_others()
{
       return HIB "只見$N" HIB "臉色煞白，身子晃了兩晃，步法散亂，便似喝醉酒一般。\n" NOR;
}

string update_msg_self()
{
        return HIR "你只覺一股莫名的惡心湧上心頭，全身上下氣血翻滾，經脈不暢。\n" NOR;
}
