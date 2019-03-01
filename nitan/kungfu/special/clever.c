// clever.c 天賦聰穎
// Created by Vin 26/8/2001

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIM "天賦聰穎" NOR; }

int perform(object me, string skill)
{
        //return notify_fail("這項技能能夠使你更快的吸收知識，不需要運用。\n");
        return notify_fail("這項技能能夠使你更快地學習技能和研究技能。\n"
                       HIC "可提高每次學習次數上限50次，提高每次研究次數上限50次。\n" NOR);
}

