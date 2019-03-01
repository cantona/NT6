//hunyuan-gong.c 混元功

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return force == "huashan-xinfa";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("huntian-qigong", 1);
        return lvl * lvl * 15 * 9 / 100 / 200;
}

int valid_learn(object me)
{
        if (me->query_skill("force", 1) < 30)
                return notify_fail("你的基本內功火候不夠，無法學習混元功。\n");

            return 1;
}

int practice_skill(object me)
{
            return notify_fail("混元功只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"hunyuan-gong/" + func;
}
