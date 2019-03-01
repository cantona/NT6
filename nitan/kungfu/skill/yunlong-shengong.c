// yunlong-shengong.c 雲龍神功
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;

inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }
int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("xuanming-shengong", 1);
        return lvl * lvl * 15 * 16 / 100 / 200;
}

int valid_force(string force)
{
        // return (force == "minggu-xinfa");
        return 1;
}

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int i, nb, nf, nh, ns, ts;
        nb = (int)me->query_skill("yunlong-xinfa", 1);
        nf = (int)me->query_skill("force", 1);
        nh = (int)me->query_skill("yunlong-shengong", 1);

        if( query("gender", me) == "無性" && nh>49 )
                return notify_fail("你無根無性，陰陽不調，難以領會高深的雲龍神功。\n");

        if ( nb < 100 && nb <= nh )
                return notify_fail("你的雲龍心法修為不夠，無法領會更高深的雲龍神功。\n");

        if ( nf < 10)
                return notify_fail("你的基本內功火候還不夠，無法領會雲龍神功。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("雲龍內功只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"yunlong-shengong/" + func;
}
int help(object me)
{
        write(HIC"\n雲龍神功："NOR"\n");
        write(@HELP

    天地會本門內功，具有自療及運功之特殊用途。


        學習要求：
                相應的雲龍心法
                基本內功10級
                太監無法學到高等級的雲龍神功
HELP
        );
        return 1;
}
