// qingming-xuangong.c 青冥玄功
// Last Modified by winder on Aug. 10 2000

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
        if (me->query_skill("force",1) < 10)
                return notify_fail("基本內功還不到火候，怎能學青冥玄功？！\n");

        return valid_public(me);
}

int practice_skill(object me)
{
        return notify_fail("青冥玄功只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"qingming-xuangong/" + func;
}
int help(object me)
{
        write(HIC"\n青冥玄功："NOR"\n");
        write(@HELP

    青冥玄功是青城派本門內功。

        學習要求：
                基本內功10級
HELP
        );
        return 1;
}
