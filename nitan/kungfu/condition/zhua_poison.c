// zhua_poison.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "zhua_poison"; }

string chinese_name() { return "凝血之毒"; }

string update_msg_others()
{
       return HIR "$N忽然打了一個哆嗦,臉上露出痛苦而詭異的笑容。\n" NOR;
}

string update_msg_self()
{
        return HIB "忽然一絲熱流自體內升起, 緩緩的浸入你四肢百"
                   "骸。你中的凝血神抓毒性發作了！\n" NOR;
}
