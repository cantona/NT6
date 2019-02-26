
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "偷天換日" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你不但智慧超羣，且工於心計。在請教他人教授技能時通常可獲取更多的幫助，同\n"
                           "時具有更高的領悟能力。學習技能時可提升學習效率10%。不需要運用。\n");
}

