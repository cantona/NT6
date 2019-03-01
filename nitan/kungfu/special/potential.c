// potential.c 乾坤無量
// Created by Vin 4/16/2001

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIB "乾坤無量" NOR; }

int perform(object me, string skill)
{
        return notify_fail("這項技能可使你在成為宗師前的潛能加倍，不需要運用。\n");
}

