// This program is a part of NITAN MudLIB
// wisdom.c 智周萬物
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "智周萬物" NOR; }

int perform(object me, string skill)
{
        return notify_fail("由於你在轉世的過程中感應到天道的無窮智慧，使\n"
                           "你的學習能力大大提高。擁有該技能者，可提高每\n"
                           "次學習、練習及研究次數上限八百次，學習、練習\n"
                           "及研究效果提升50%。 \n");
}
