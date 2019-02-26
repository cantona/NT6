// This program is a part of NITAN MudLIB
// capture.c 遁影擒蹤
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIM "遁影擒蹤" NOR; }

int perform(object me, string skill)
{
        if (me->query_skillo("count", 1) < 800)
                me->set_skill("count", 800);

        if (me->query_skillo("mathematics", 1) < 800)
                me->set_skill("mathematics", 800);

        return notify_fail("你在轉生過程中縱觀天象，察覺到了人世間的諸多\n"
                           "奧祕，眾生百態盡收眼底。此後不再受到架力卸招\n"                          
                           "之技的迷惑。轉生後可得到陰陽八卦及算術八百級。\n"
                           "同時，擁有該技能者可同時施展左右互搏之術，不\n"
                           "再受到陰陽八卦的限制。    \n");
}