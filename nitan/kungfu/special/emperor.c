// emperor.c  真命天子

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "真命天子" NOR; }

int perform(object me, string skill)
{
        return notify_fail("真命天子這項技能不需要運用。\n");
}
