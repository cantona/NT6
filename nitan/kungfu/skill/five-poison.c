// five-poison.c 五毒毒技
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;

string type() { return "knowledge"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

void skill_improved(object me)
{}

int valid_learn(object me)
{
        mapping myfam;
        myfam=query("family", me);
        if (!myfam || (myfam["family_name"] != "五毒教"))
                return notify_fail("你不是五毒教弟子，不能修煉五毒毒技。\n");
        return 1;

}

int help(object me)
{
        write(HIC"\n五毒毒技："NOR"\n");
        write(@HELP

    五毒毒技為雲南五毒教獨門毒技。也就是用毒的技巧，是五毒
教弟子必修的功夫，關係到投毒的成敗和暗器的傷害力。

        學習要求：
                無
HELP
        );
        return 1;
}
