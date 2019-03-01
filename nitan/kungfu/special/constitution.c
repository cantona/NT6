// constitution.c 鎮蘊七星
// Created by Vin 1/9/2001

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "鎮蘊七星" NOR; }

int perform(object me, string skill)
{
        return notify_fail("這項技能能夠使你根骨更高，不需要運用。\n");
}

