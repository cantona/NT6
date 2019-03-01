
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIW "仙風道骨" NOR; }

int perform(object me, string skill)
{
        return notify_fail("這項技能能夠使你更快地學習技能和研究技能。\n"
                       HIC "可提高每次學習次數上限50次，提高每次研究次數上限50次。\n" NOR);
}

