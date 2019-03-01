// This program is a part of NITAN MudLIB
// sophistry.c 詭辯奇學
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIC "詭辯奇學" NOR; }

int perform(object me, string skill)
{
        return notify_fail("精通諸子百家的各種思想學說，在辨術方面獨領風\n"
                           "騷，擅此法者可淆亂是非，點石成金，指鹿為馬也\n"
                           "不稱奇。任務連續數限制提升一倍，擁有該特技的\n"
                           "玩家在取消師門任務時，當前任務數不歸零，且取\n"
                           "消任務不降低江湖威望等相關能力。\n");
}
