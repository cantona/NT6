// wrath.c 憤怒之心
// Created by Vin 25/5/2002

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIR "憤怒之心" NOR; }

int perform(object me, string skill)
{
        return notify_fail("這項技能能夠增加你的加怒上限，不需要運用。\n");
}

