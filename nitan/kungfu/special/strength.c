// strength.c 麒麟血臂
// Created by Vin 1/9/2001

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIR "麒麟血臂" NOR; }

int perform(object me, string skill)
{
        return notify_fail("這項技能能夠使你膂力更高，不需要運用。\n");
}

