// greedy.c 饕餮轉世
// Created by Vin 25/5/2002

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIR "饕餮轉世" NOR; }

int perform(object me, string skill)
{
        return notify_fail("這項技能能夠增加你的食物及飲水上限，不需要運用。\n");
}

