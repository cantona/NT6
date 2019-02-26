// qijin.c 奇筋異骨
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIG "奇筋異骨" NOR; }

int perform(object me, string skill)
{
        return notify_fail(HIG "此天性者天生骨骼精奇，乃百年難遇的練武奇才。\n"
                               "擁有此技能者可使研究技能次數限制加倍，即如果你\n"
                               "目前每次可以研究300次， 則擁有該技能後可每次研\n"
                               "究600次。同時， 擁有該技能者在研究技能時所消耗\n"
                               "的潛能減少10%，即如果你研究600次所消耗的潛能原\n"
                               "為600點，則此時為540點。如研究次數小於10次則不\n"
                               "產生減少潛能消耗10%的效果。\n" NOR);

}