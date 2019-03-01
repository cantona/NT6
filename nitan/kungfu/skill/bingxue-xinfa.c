// bingxue-xinfa.c 冰雪心法
// Last Modified by winder on Jul. 15 2001

#include <ansi.h>;

inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

int valid_enable(string usage) { return usage=="force"; }

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("bingxue-xinfa", 1);

        if ( me->query_skill("force", 1) < 10)
                return notify_fail("你的基本內功還不到火候。\n");
        if( query("gender", me) == "無性" && lvl>49 )
                return notify_fail("你無根無性，陰陽不調，難以領會高深的冰雪心法。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("冰雪心法只能用學的，或是從運用(exert)中增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"bingxue-xinfa/" + func;
}
int help(object me)
{
        write(HIC"\n冰雪心法："NOR"\n");
        write(@HELP

    冰雪心法是雪山凌霄城的內功心法，是雪山派弟子本門內功。

        學習要求：
                基本內功10級
                太監無法領悟50級以上的冰雪心法
HELP
        );
        return 1;
}
