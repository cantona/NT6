// xidu-poison.c 西毒毒技
// Last Modified by winder on Mar. 10 2000
// Modified by Java Mar.1998

#include <ansi.h>;
inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

int valid_learn(object me)
{
        mapping myfam;
        myfam=query("family", me);
        if (!myfam || (myfam["family_name"] != "白駝山派"))
                return notify_fail("你不是白駝山弟子，不能修煉西毒毒技。\n");
        if( query("shen", me) <= 0 )
          return notify_fail("修煉西毒毒技要心狠手辣，姦惡歹毒，你的表現還不夠！\n");
        return 1;
}

int practice_skill(object me)
{
        return notify_fail("西毒毒技只能靠學習來提高。\n");
}
int help(object me)
{
        write(HIC"\n西毒毒技："NOR"\n");
        write(@HELP

    西毒弟子下毒必具武功，下毒的效果和西毒毒技的高低有很大
的關系。

        學習要求：
                名門正派的心法不能學
                非白駝山派弟子不能學
HELP
        );
        return 1;
}
