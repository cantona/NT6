// shenlong-xinfa.c 神龍心法

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        // return force == "shedao-neigong";
        return 1;
}

int valid_learn(object me)
{
        if( query("gender", me) == "無性" && 
        (int)me->query_skill("shenlong-xinfa", 1) > 49)
                return notify_fail("你無根無性，陰陽不調，難以領會高深的神龍心法。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
    return notify_fail("神龍心法只能通過學或是從運用(exert)中增加熟練度。\n");
}

string exert_function_file(string func)
{
    return __DIR__"shenlong-xinfa/" + func;
}