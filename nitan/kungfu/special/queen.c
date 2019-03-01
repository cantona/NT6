// queen.c  九天玄女

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIR "九天玄女" NOR; }

int perform(object me, string skill)
{
        return notify_fail("九天玄女這項技能不需要運用。\n");
}
