// intellect.c 罡睿神慧
// Created by Vin 1/9/2001

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIG "罡睿神慧" NOR; }

int perform(object me, string skill)
{
        return notify_fail("這項技能能夠使你悟性更高，不需要運用。\n");
}

