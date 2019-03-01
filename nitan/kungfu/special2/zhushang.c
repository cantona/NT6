// zhushang.c 諸傷之術
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIM "諸傷之術" NOR; }

int perform(object me, string skill)
{
        return notify_fail("此天性者在轉世過程中參悟出世間萬物生\n"
                           "存之理，能在受傷時驅使萬物之靈使對手\n"
                           "也同樣受到傷害。\n");
}