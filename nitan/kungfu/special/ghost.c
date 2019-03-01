// This program is a part of NITAN MudLIB
// ghost.c 六陰鬼脈
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIB "六陰鬼脈" NOR; }

int perform(object me, string skill)
{
        return notify_fail("乃世間千年一遇的特殊經脈，此脈至陰至寒，身俱\n"
                           "此經脈的嬰兒常被誤診為寒毒纏身，醫而不得其法，\n"
                           "導致幼年夭折。擁此經脈修煉各種內功將事半功倍。\n"
                           "無論男女，均可直接修煉辟邪劍法或是葵花魔功，\n"
                           "無需再作自宮。擁有該技能的人研究任何可以激發\n"
                           "為內功的技能時，研究效率提高50%。 而內力上限\n"
                           "也可提高50%。\n");
}