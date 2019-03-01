inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return force == "nei-bagua" ||
               force == "bagua-xinfa" ||
               force == "shangjia-neigong";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("nei-bagua", 1);
        return lvl * lvl * 15 * 8 / 100 / 200;
}

int valid_learn(object me)
{
        if( query("gender", me) == "無性" && 
            (int)me->query_skill("nei-bagua", 1) > 49)
                return notify_fail("你無根無性，陰陽難調，無法學習更高深的內八卦。\n");

        if ((int)me->query_skill("force", 1) < 80)
                return notify_fail("你的基本內功火候還不夠。\n");

        if ((int)me->query_skill("wai-bagua", 1) < 100)
                return notify_fail("你的外八卦功夫火候還不夠。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("內八卦只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"nei-bagua/" + func;
}