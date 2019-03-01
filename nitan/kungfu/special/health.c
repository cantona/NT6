// health.c 內斂乾坤
// Created by Vin 26/8/2001

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "內斂乾坤" NOR; }

int perform(object me, string skill)
{
        return notify_fail("這項技能能夠增加你的最大氣血，不需要運用。\n");
}

