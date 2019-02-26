// This program is a part of NITAN MudLIB
// nopoison.c 羣邪辟易
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIM "羣邪辟易" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你轉世時自餓鬼道輪迴後所擁有的體質，從此之後\n"
                           "百毒不侵，諸病不染。不但能將七星海棠、斷腸花\n"
                           "以及常見的毒素於無形，甚至於吸星大法、乾坤大\n"
                           "挪移之類神功的反噬也能輕易化解。且擁有此體質\n"
                           "的玩家研究和汲取時提升效果50%。\n");
}