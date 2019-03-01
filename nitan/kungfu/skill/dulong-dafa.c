// dulong-dafa.c 蛇島  毒龍大法
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
#include "force.h";
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
        mapping skills;
        string *sname;

        int lvl = (int)me->query_skill("dulong-dafa", 1);
        int t = 1, i, j;
        int other_force = 0;

        for (j = 1; j < lvl / 10; j++) t *= 2;
/*
        if( !query("yijin_wan", me) )
                return notify_fail("你未曾服食教主的豹胎易經丸，沒有根基，無法學習毒龍大法。\n");

        if( query("yijin_wan", me)<query("age", me)-13 )
                return notify_fail("你未曾每年按期服食教主的豹胎易經丸，無法繼續學習毒龍大法。\n");

*/
        if ( (int)me->query_skill("force", 1) < 10 ||
                (int)me->query_skill("force", 1)/2 < lvl/3 )
                return notify_fail("你的基本內功火候還不夠，無法領會毒龍大法。\n");
        if( lvl>10 && query("shen", me)>t*100 && 
                (me->query_skill("taoism", 1) ||
                me->query_skill("buddhism", 1)) )
                return notify_fail("你尚不適宜學習毒龍大法。\n");
        return valid_public(me);
}

int practice_skill(object me)
{
        return notify_fail("毒龍大法只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"dulong-dafa/" + func;
}

int help(object me)
{
        write(HIC"\n毒龍大法："NOR"\n");
        write(@HELP

    毒龍大法為神龍教本門內功。

        學習要求：
                基本內功10級
                不能修習禪宗或道家心法
HELP
        );
/*                定期服食豹胎易經丸 */
        return 1;
}
