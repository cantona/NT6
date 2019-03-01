
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIG "天生奇骨" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你擁有天生超強療傷和逼毒能力，且內力上限破格提升5%，不需要運用。\n");
}

