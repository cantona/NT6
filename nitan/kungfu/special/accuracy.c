// accuracy.c 精準射擊
// Created by Vin 4/16/2001

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIC "精準射擊" NOR; }

int perform(object me, string skill)
{
        return notify_fail("這項技能可使你運用弓箭的命中率加倍，不需要運用。\n");
}

