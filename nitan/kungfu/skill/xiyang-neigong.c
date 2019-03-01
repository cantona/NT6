// xiyang-neigong 西洋內功

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("xiyang-shengong", 1);
        return lvl * lvl * 15 * 4 / 100 / 200;
}

int valid_learn(object me)
{
        if ((int)me->query_skill("force", 1) < 40)
                return notify_fail("你的基本內功火候還不夠，還不能學習西洋內功。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("西洋內功只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"xiyang-neigong/" + func;
}