
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIM "流星慧眼" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你擁有超乎常人的洞察能力，戰鬥中可提升平招命中+30%。不需要運用。\n");
}

