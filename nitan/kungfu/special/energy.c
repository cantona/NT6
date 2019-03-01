// energy.c 聚魄還虛
// Created by Vin 26/8/2001

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIC "聚魄還虛" NOR; }

int perform(object me, string skill)
{
        return notify_fail("這項技能能夠增加你的最大精氣，不需要運用。\n");
}

