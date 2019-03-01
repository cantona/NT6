// zhanzhuang-gong.c 南少林 四平大馬站樁功
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit FORCE;
#include "force.h"
string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int i, nb, nf, nh, ns, ts;

        nb = (int)me->query_skill("buddhism", 1);
        nf = (int)me->query_skill("force", 1);
        nh = (int)me->query_skill("zhanzhuang-gong", 1);
        ns=query("guilty", me);

        if( query("couple/have_couple", me) )
                return notify_fail("你塵緣未了，無法學習四平大馬站樁功！\n");
        if( query("sex/number", me) )
                return notify_fail("你已經破了色戒，無法再學習四平大馬站樁功！\n");
        if ( nb < 100 && nb <= nh )
                return notify_fail("你的禪宗心法修為不夠，無法領會更高深的四平大馬站樁功。\n");
        if ( nf < 10)
                return notify_fail("你的基本內功火候還不夠，無法領會四平大馬站樁功。\n");
        if ( ns > 0 ) 
                return notify_fail("你屢犯僧家數戒，無法領會更高深的四平大馬站樁功。\n");

  return valid_public(me,"yijinjing");
}

int practice_skill(object me)
{
        return notify_fail("四平大馬站樁功只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"zhanzhuang-gong/" + func;
}
int help(object me)
{
        write(HIC"\n站樁功："NOR"\n");
        write(@HELP

    站樁功全稱四平大馬站樁功，為南少林派本門內功。
    南少林特注重根基。要求弟子馬步站穩，日日都需練習。四平指的是
紮馬步樁時，頭平、肩平、手平和膝平。練習時，常放置水碗于這些部位，
練習過程中，不允許水溢出。

        學習要求：
                基本內功10級
                禪宗心法修為不低于四平大馬站樁功
                不犯其它戒律
HELP
        );
        return 1;
}
