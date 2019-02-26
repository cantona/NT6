// might.c 狂暴鐵拳
// Created by Vin 25/5/2002

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIW "狂暴之力" NOR; }

int perform(object me, string skill)
{
        return notify_fail("此乃自遠古流傳至今的一條稀有血脈，現存於世也不過寥寥無幾。據\n"
                           "傳擁有此血脈者往往身強體壯，力大無窮。擁有狂暴血脈之人，可以\n"
                           "使其的加力上限提高20%。\n");
}

