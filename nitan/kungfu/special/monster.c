// This program is a part of NITAN MudLIB
// monster.c 天妖臨世
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIM "天妖臨世" NOR; }

int perform(object me, string skill)
{
        return notify_fail("此天性者在轉世過程中參悟出世間萬物生\n"
                           "存之理，能在受傷時驅使萬物之靈使對手\n"
                           "也同樣受到傷害。\n");
}