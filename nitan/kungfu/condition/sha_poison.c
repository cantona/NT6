#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "sha_poison"; }

string chinese_name() { return "砂毒"; }

string update_msg_others()
{
       return HIR "$N" HIR "臉色霎地變的煞白，全身不停的顫抖。\n" NOR;
}

string update_msg_self()
{
        return HIR "你只覺毒氣攻心，頓時感到一股莫名的噁心，全身癱軟無力！\n" NOR;
}

