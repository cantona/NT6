// kurong-changong.c 枯榮禪功

#include <ansi.h>;

inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

int valid_force(string force)
{
        return 1;
        return force == "xiantian-gong" ||
               force == "quanzhen-xinfa"  ||
               force == "duanshi-xinfa";
}

int query_neili_improve(object me)
{
            int lvl;

            lvl = (int)me->query_skill("kurong-changong", 1);
            return lvl * lvl * 15 * 15 / 100 / 200;
}

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int nb, nk;
        int lvl = (int)me->query_skill("kurong-changong", 1);

        if( query("gender", me) == "無性" && lvl>49 )
                return notify_fail("你無根無性，陰陽不調，難以領會高深的枯榮禪功。\n");

        if ((int)me->query_skill("force", 1) < 20)
                return notify_fail("你的基本內功火候還不夠。\n");

        nb = (int)me->query_skill("buddhism", 1);
        nk = (int)me->query_skill("kurong-changong", 1);

        if (nb < 120 && nb <= nk)
                return notify_fail("你的禪宗心法修為不夠，無法領會更高深的枯榮禪功。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("枯榮禪功只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"kurong-changong/" + func;
}


int help(object me)
{
        write(HIC"\n枯榮禪功："NOR"\n");
        write(@HELP

    有常無常，雙樹枯榮，南北西東，非假非空！
    佛門奇功，天龍寺枯榮長老精擅此技。相傳釋迦牟尼在桫欏雙
樹之間入滅，代表了非枯非榮、非假非空的最高境界，後世弟子便
以此為修行之法，靜參枯禪。是為枯榮禪功之來由。
    為天南大理段家的本門內功。

        學習要求：
                基本內功10級
                不能是太監
HELP
        );
        return 1;
}
