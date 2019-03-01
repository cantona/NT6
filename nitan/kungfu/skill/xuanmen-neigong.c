inherit FORCE;

int valid_enable(string usage)
{
        return usage == "force";
}

int valid_force(string force)
{
        return force == "xiantian-gong" ||
               force == "quanzhen-xinfa" ;
}

int query_neili_improve(object me)
{
    int lvl;

    lvl = (int)me->query_skill("xuanmen-neigong", 1);
    return lvl * lvl * 15 * 8 / 100 / 200;
}

int valid_learn(object me)
{
        if ((int)me->query_skill("force", 1) < 60)
                return notify_fail("你的基本內功火候還不夠。\n");

        if( query("gender", me) == "無性" && me->query_skill("xuanmen-neigong",1)>29 )
                return notify_fail("你無根無性，陰陽不調，難以領會高深的玄門內功。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("玄門內功只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"xuanmen-neigong/" + func;
}