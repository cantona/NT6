// iceshock.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "iceshock"; }

string chinese_name() { return "寒毒"; }

string update_msg_others()
{
       return HIR "$N忽然打了一個哆嗦。\n" NOR;
}

string update_msg_self()
{
        return HIB "你覺得就像掉到了冰窖裡一樣，看來是寒毒發作了！\n" NOR;
}
