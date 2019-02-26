// xuantian-wuji 玄天無極功

#include <ansi.h>;
#include "force.h";
inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int nl, ng, nf, nx;
        nf = (int)me->query_skill("force", 1);
        ng = (int)me->query_skill("goplaying", 1);
        nl = (int)me->query_skill("luteplaying", 1);
        nx = (int)me->query_skill("xuantian-wuji", 1);

        if ( nf < 20)
                return notify_fail("你的基本內功火候還不夠，無法領會玄天無極功。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("玄天無極功只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"xuantian-wuji/" + func;
}
int help(object me)
{
        write(HIC"\n玄天無極功："NOR"\n");
        write(@HELP

    玄天無極功是崑崙派的本門內功。

        學習要求：
                基本內功10級
                相當的琴棋技藝的造詣
HELP
        );
        return 1;
}
