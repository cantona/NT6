
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY"日月齊輝" NOR; }

int perform(object me, string skill)
{
        return notify_fail("二轉時你受到日月之輝的照耀而感悟，對武學的領悟更上一層，此技能可提升練習次數50次。\n");
}

