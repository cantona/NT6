// guimai.c 六陰鬼脈
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIM "六陰鬼脈" NOR; }

int perform(object me, string skill)
{
        return notify_fail("乃世間千年一遇的特殊經脈，此脈至陰至\n"
                           "寒，身俱此經脈的嬰兒常被誤診為寒毒纏\n"
                           "身，醫而不得其法，導致幼年夭折。但若\n"
                           "活過三歲不死者，此後修煉各種內功將事\n"
                           "半功倍，且內力修為比常人更高。無論男\n"
                                                   "女，均可直接修煉辟邪劍法或是葵花魔功，\n"
                                                   "無需再作自宮。\n"
                                                   "注：擁有該技能的人研究任何可以激發為\n"
                                                   "內功的技能時，研究速度提高10%。而內力\n"
                                                   "上限也可提高30%。\n");
}