// cunning.c 八面玲瓏
// Created by Vin 26/3/2002

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIC "八面玲瓏" NOR; }

int perform(object me, string skill)
{
        return notify_fail("這項技能能夠使你獲得更多的門派貢獻值，不需要運用。\n");
}

