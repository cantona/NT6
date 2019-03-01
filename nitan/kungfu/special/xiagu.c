// zhushang.c 諸傷之術
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIM "俠骨丹心" NOR; }

int perform(object me, string skill)
{
        return notify_fail("被動技能，不需要施展，能大幅度提高精力上限、提高精力及氣血恢復速度。\n");
}