// huashan-neigong.c 華山心法

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int level = (int)me->query_skill("huashan-neigong", 1);
        if( query("gender", me) == "無性" && level>49 )
                return notify_fail("你無根無性，陰陽不調，難以領會高深的華山內功。\n");
        return ::valid_learn(me);
}

int valid_force(string force) { return 1; }

int query_neili_improve(object me)
{
        int lvl;
        lvl = (int)me->query_skill("huashan-neigong", 1);
        return lvl * lvl * 18 * 15 / 100 / 200;
}

int practice_skill(object me)
{
        return notify_fail("華山心法只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"huashan-neigong/" + func;
}

