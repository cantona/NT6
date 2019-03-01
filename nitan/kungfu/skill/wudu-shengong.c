// wudu-shengong.c 五毒神功
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>
inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return 1;
        return force == "hamagong" ||
               force == "xiuluo-yinshagong" ||
               force == "shunxi-qianli";
}

int valid_learn(object me)
{
        int nf;
        nf = (int)me->query_skill("force", 1);

        if ( nf < 10)
                return notify_fail("你的基本內功火候還不夠，無法領會五毒神功。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("五毒神功只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"wudu-shengong/" + func;
}
int help(object me)
{
        write(HIC"\n五毒神功："NOR"\n");
        write(@HELP

    五毒教必修的一門功夫，五毒弟子就是靠它才可以日夜與毒蟲
毒藥為伴。

        學習要求：
                基本內功10級
HELP
        );
        return 1;
}
