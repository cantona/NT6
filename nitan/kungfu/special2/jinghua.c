// jinghua.c 仙音菁華
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIM "仙音凈化" NOR; }

int perform(object me, string skill)
{
        return notify_fail("在轉生的過程中你受到了天界仙音的凈化，\n"
                           "轉世後自身的先天得到了極大的提升。此\n"
                           "項技能可以使你的先天悟性、根骨、臂力\n"
                           "以及先天身法破格提升兩點。\n");

}