
#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "hanbingdu"; }

string chinese_name() { return "冰魄銀針劇毒"; }

string update_msg_others()
{
        return HIW "$N" HIW "臉色蒼白，四肢僵硬，全身上下透出陣"
               "陣寒氣。\n" NOR;
}

string update_msg_self()
{
        return HIW "你只覺全身冰冷無比，四肢百骸難受之極，如墮"
               "冰獄。\n" NOR;
}

