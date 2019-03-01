// youth.c 駐顏
// Created by Doing Lu 10/7/2K

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIG "天顏永駐" NOR; }

int perform(object me, string skill)
{
        return notify_fail("這項技能能夠保持你青春永駐，不需要運用。\n");
}