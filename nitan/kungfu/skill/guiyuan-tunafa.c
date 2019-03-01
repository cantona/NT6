// guiyuan-tunafa.c 鐵掌幫 歸元吐納法
// Last Modified by winder on Nov. 15 2000

#include <ansi.h>;
#include "force.h"
inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }

int valid_enable(string usage) { return usage == "force"; }
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

int valid_learn(object me)
{
        int nf;
        
        nf = (int)me->query_skill("force", 1);
        if ( nf < 10)
                return notify_fail("你的基本內功火候還不夠，無法領會歸元吐吶法。\n");

        return valid_public(me);
}

int practice_skill(object me)
{
        return notify_fail("歸元吐吶法只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"guiyuan-tunafa/" + func;
}
int help(object me)
{
        write(HIM"\n歸元吐納法："NOR"\n");
        write(@HELP

    鐵掌幫的內功，具自療、他療及運功之用。

        學習要求：
                基本內功10級
HELP
        );
        return 1;
}
