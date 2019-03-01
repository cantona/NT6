// diwang.c 帝王之星
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIM "帝王之星" NOR; }

int perform(object me, string skill)
{
        return notify_fail(HIM "此天性者擁有帝王之像，四項先天屬性可永久各加兩\n"
                               "點。同時，內力上限和精力上限各提升20%， 氣血恢\n"
                               "復速度提升30%。\n" NOR);

}