// lonely.c  天煞孤星

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return CYN "天煞孤星" NOR; }

int perform(object me, string skill)
{
        return notify_fail("天煞孤星這項技能不需要運用。\n");
}
