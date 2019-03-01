inherit FORCE;

int valid_enable(string usage)
{
            return usage == "force";
}

int valid_force(string force)
{
        return 1;
        return force == "xiantian-gong" ||
               force == "quanzhen-xinfa"  ||
               force == "kurong-changong";
}

string exert_function_file(string func)
{
        return __DIR__"duanshi-xinfa/" + func;
}

int valid_learn(object me)
{
        if ((int)me->query_skill("force", 1) < 10)
                return notify_fail("你的基本內功火候還不夠，還不能學習段氏心法。\n");

        if( query("gender", me) == "無性"
           && (int)me->query_skill("duanshi-xinfa") > 49)
                    return notify_fail("你無根無性，陰陽不調，難以領會高深的段氏心法。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("段氏心法只能用學(learn)的來增加熟練度。\n");
}