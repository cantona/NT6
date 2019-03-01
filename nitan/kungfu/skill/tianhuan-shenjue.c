inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return force == "riyue-xinfa" ||
               force == "xixing-dafa" ||
               force == "yijinjing" ||
               force == "kuihua-mogong";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("tianhuan-shenjue", 1);
        return lvl * lvl * 15 * 8 / 100 / 200;
}

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("tianhuan-shenjue", 1);

        if ((int)me->query_skill("force", 1) < 50)
                return notify_fail("你的基本內功火候還不夠。\n");

        // 因為是日月神教的內功，所以對無性的學習限制放寬
        if( query("gender", me) == "無性" && lvl>99 )
                return notify_fail("你無根無性，陰陽不調，難以領會高深的天寰神訣。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("天寰神訣只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"tianhuan-shenjue/" + func;
}