inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("xuanming-shengong", 1);
        return lvl * lvl * 15 * 16 / 100 / 200;
}

int valid_force(string force)
{
        // return (force == "minggu-xinfa");
        return 1;
}

int valid_learn(object me)
{
        if( query("con", me)<30 )
                return notify_fail("你先天根骨不足，無法修煉玄冥神功。\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的基本內功火候還不夠，還不能學習玄冥神功。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("玄冥神功只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"xuanming-shengong/" + func;
}
