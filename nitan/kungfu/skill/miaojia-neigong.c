inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int query_neili_improve(object me)
{
    int lvl;

    lvl = (int)me->query_skill("miaojia-neigong", 1);
    return lvl * lvl * 15 * 4 / 100 / 200;
}

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("miaojia-neigong", 1);

        if( query("gender", me) == "無性" && lvl>49 )
                return notify_fail("你無根無性，陰陽不調，難以領會高深的苗家內功。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
    return notify_fail("苗家內功只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
    return __DIR__"miaojia-neigong/" + func;
}