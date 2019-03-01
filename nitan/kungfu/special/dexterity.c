// dexterity.c 玲瓏玉軀
// Created by Vin 1/9/2001

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIW "玲瓏玉軀" NOR; }

int perform(object me, string skill)
{
        return notify_fail("這項技能能夠使你身法更高，不需要運用。\n");
}

