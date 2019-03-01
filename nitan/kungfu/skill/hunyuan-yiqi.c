// hunyuan-yiqi.c 少林 混元一氣功

#include <ansi.h>;
inherit FORCE;

string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point() { return 1; }

int valid_enable(string usage) { return usage == "force"; }
int query_neili_improve(object me)
{
        int lvl;

        if( query("sex", me) )
                return 0;

        lvl = (int)me->query_skill("hunyuan-yiqi", 1);
        return lvl * lvl * 15 * 21 / 100 / 200;
}

int valid_force(string force)
{
/*
        return force == "yijinjing" ||
               force == "taiji-shengong" ||
               force == "wudang-xinfa" ||
*/
        return 1;
}
int valid_learn(object me)
{
        int i, nb, nf, nh, ns, ts;

        nb = (int)me->query_skill("buddhism", 1);
        nf = (int)me->query_skill("force", 1);
        nh = (int)me->query_skill("hunyuan-yiqi", 1);
        ns=query("guilty", me);

        if ((int)me->query_skill("force", 1) < 10)
                return notify_fail("你的基本內功火候還不夠。\n");

        if( query("couple/have_couple", me) )
                return notify_fail("你塵緣未了，無法再學習混元一氣功！\n");

        if( query("sex/number", me) )
                return notify_fail("你已經破了色戒，無法再學習混元一氣功！\n");

        if( query("gender", me) != "男性" )
                return notify_fail("你非童男之體，不能練習混元一氣功。\n");

        if ( nb < 100 && nb <= nh )
                return notify_fail("你的禪宗心法修為不夠，無法領會更高深的混元一氣功。\n");

        if ( nf < 10)
                return notify_fail("你的基本內功火候還不夠，無法領會混元一氣功。\n");

        if ( ns > 0 )
                return notify_fail("你屢犯僧家數戒，無法領會更高深的混元一氣功。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("混元一氣功只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"hunyuan-yiqi/" + func;
}

int help(object me)
{
        write(HIC"\n混元一氣功："NOR"\n");
        write(@HELP

    混元一氣功為少林派本門內功。

        學習要求：
                基本內功10級
                不能破色戒的童男之身
                禪宗心法修為不低于混元一氣功
                不犯其它戒律
HELP
        );
        return 1;
}
