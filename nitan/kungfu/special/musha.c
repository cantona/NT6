// This program is a part of NITAN MudLIB
// musha.c 武星轉世
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIR "武星轉世" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你在轉世時巧遇武曲星投胎轉世，獲\n"
                           "取武曲星附體轉生，擁有常人沒有的\n"
                           "武學領悟能力。轉生後擁有該技能可\n"
                           "以提高所有武學研究速度百分之五十，\n"
                           "汲取實戰體會速度提高百分之五十。\n");
}