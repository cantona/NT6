// lucky.c 福星高照
// Created by Vin 6/13/2002

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "福星高照" NOR; }

int perform(object me, string skill)
{
        return notify_fail("這項技能可提升你服用仙丹的成功率，不需要運用。\n");
}

