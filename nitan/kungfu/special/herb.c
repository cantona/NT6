// herb.c 本草知識
// Created by Vin 6/13/2002

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIG "本草知識" NOR; }

int perform(object me, string skill)
{
        return notify_fail("這項技能可使你更快更有效的吸收各類藥物，不需要運用。\n");
}

