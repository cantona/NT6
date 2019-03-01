// zhuha.c 朱蛤奇緣
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIM "朱蛤奇緣" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你年輕時因機緣巧合，碰巧服用了萬毒至\n"
                           "尊的莽牯朱蛤，從此之後百毒不侵。\n");
}