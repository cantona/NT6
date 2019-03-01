inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return 1;
        return force == "tiezhang-xinfa" ||
               force == "tianlei-shengong" ||
               force == "wuqing-xinfa" ||
               force == "bingxin-jue";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("tianlei-shengong", 1);
        return lvl * lvl * 15 * 10 / 100 / 200;
}

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("tianlei-shengong", 1);

        if ((int)me->query_skill("force", 1) < 70)
                return notify_fail("你的基本內功火候還不夠。\n");

        if( query("gender", me) == "無性" && lvl>49 )
                return notify_fail("你無根無性，陰陽不調，難以領會高深的天雷神功。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("天雷神功只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"tianlei-shengong/" + func;
}