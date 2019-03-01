
// guimai.c 天擎秘氣
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIM "天擎秘氣" NOR; }

int perform(object me, string skill)
{
        return notify_fail("參破宇宙奧妙，窺視武道至高境界的運功法門，不需要施展，可增加內力和精力上限5%\n");
}

