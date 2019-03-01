
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "乾坤精魄" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你天生比一般人擁有更高的精氣修為，可提升最大精氣值30%。不需要運用。\n");
}

