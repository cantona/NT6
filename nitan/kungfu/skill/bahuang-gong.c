// bahuang-gong.c 八荒六合唯我獨尊功
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit FORCE;

string type() { return "martial"; }
string martialtype() { return "force"; }
int valid_enable(string usage) { return usage == "force"; }
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

int valid_force(string force)
{
        return 1;
        return force == "xiaoyao-xinfa" ||
               force == "lingjiu-xinfa" ||
               force == "beiming-shengong" ||
               force == "xiaowuxiang" ||
               force == "wudoumi-shengong";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("bahuang-gong", 1);
        return lvl * lvl * 15 * 16 / 100 / 200;
}

int valid_learn(object me)
{
        if ((int)me->query_skill("force", 1) < 80)
                return notify_fail("你的基本內功火候還不夠。\n");

        if( query("gender", me) == "無性" && 
        (int)me->query_skill("bahuang-gong", 1) > 49)
                return notify_fail("你無根無性，陰陽不調，難以領會高深的八荒六合唯我獨尊功。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("八荒六合唯我獨尊功只能用學(learn)的來提高。\n");
}
string exert_function_file(string func)
{
        return __DIR__"bahuang-gong/" + func;
}

int help(object me)
{
        write(HIC"\n八荒六合唯我獨尊功："NOR"\n");
        write(@HELP

    八荒六合唯我獨尊功是靈鷲宮至高無上的內功，須以最上乘內
功為根基。這功夫威力奇大，卻有一個大大的不利之處，每三十年，
便要返老還童一次。

        學習要求：
                靈鷲宮弟子
                基本內功10級
HELP
        );
        return 1;
}
