// buddhism.c 禪宗心法
// Last Modified by winder on Mar. 10 2000

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
        if( query("guilty", me)>0 )
                return notify_fail("你屢犯僧家數戒，塵俗之心太重，無法修煉禪宗心法。\n");

        if( query("class", me) != "bonze" && me->query_skill("buddhism",1) >= 350 )
                return notify_fail("你凡心重，不出家，怎麼能繼續修煉禪宗心法。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("禪宗心法只能靠學(learn)來提高。\n");
}

void skill_improved(object me)
{
        if( me->query_skill("buddhism",1) == 120 && !query("sl_gift/int", me) )
        {
                addn("int", 1, me);
                set("sl_gift/int", 1, me);
                tell_object(me, HIM "\n你的禪宗心法學有所成，提高了你的智力。\n" NOR);
        }
}

int help(object me)
{
        write(HIC"\n禪宗心法："NOR"\n");
        write(@HELP

    少林弟子的必修課。少林派創派祖師達摩乃是天竺禪宗大師，
又是東土禪宗第一祖，少林弟子自應以修習禪宗，精研佛法為任。
配合混元一氣功可以長精，精增加的程度取決於混元一氣功和禪宗
心法等級的高低。

        學習要求：
                犯戒或非出家人無法領悟
                與道家心法和紫氲吟不能兼學
HELP
        );
        return 1;
}
