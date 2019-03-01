
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIM "練武奇才" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你出生于武學世家，天生聰穎，乃練武上等之材。研究技能時可提升5%效率。不需要運用。\n");
}

