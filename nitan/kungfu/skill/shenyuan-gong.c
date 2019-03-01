// shenyuan-gong.c 神元功
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;

inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }
int valid_force(string force) { return 1; }

int query_neili_improve(object me)
{
        int lvl;
        lvl = (int)me->query_skill("shenyuan-gong", 1);
        return lvl /10 * lvl /10 * 20 * 15 / 10 / 20;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("shenyuan-gong", 1);
        if( query("gender", me) == "無性" && lvl>49 )
                return notify_fail("你無根無性，陰陽不調，難以領會高深的神元功。\n");
        if ((int)me->query_skill("force", 1) < 10)
                return notify_fail("你的基本內功火候還不夠，無法領會神元功。\n");
        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("神元功只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"shenyuan-gong/" + func;
}
int help(object me)
{
        write(HIC"\n神元功："NOR"\n");
        write(@HELP

    神元功是江南姑蘇慕容世家的本門內功。

        學習要求：
                基本內功10級
HELP
        );
        return 1;
}
