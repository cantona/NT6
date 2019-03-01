// mystery.c 玄黃聚納
// Created by Doing Lu 10/7/2K

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "玄黃聚納" NOR; }

int perform(object me, string skill)
{
        return notify_fail("這項技能能夠提升你的最大內力，不需要運用。\n");
}