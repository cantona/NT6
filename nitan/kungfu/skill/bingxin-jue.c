inherit FORCE;

int valid_enable(string usage)
{
        return usage == "force";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("bingxin-jue", 1);
        return lvl * lvl * 15 * 18 / 100 / 200;
}

int valid_force(string force)
{
        return 1;
}

int valid_learn(object me)
{
        if( query("gender", me) == "無性" && query("bingxin-jue", me)>99 )
                return notify_fail("你無根無性，陰陽不調，難以領會高深的冰心決。\n");

        if( query("int", me)<26 )
                return notify_fail("你覺得冰心決深奧無比，一時難以領會。\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的基本內功火候還不夠，還不能學習冰心決。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("冰心決只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"bingxin-jue/" + func;
}
