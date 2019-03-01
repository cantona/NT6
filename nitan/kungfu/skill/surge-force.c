// surge-force.c 怒海狂濤

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force) { return 1; }

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("surge-force", 1);
        return lvl * lvl * 15 * 19 / 100 / 200;
}

int valid_learn(object me)
{
        if( query("gender", me) != "男性" )
                return notify_fail("你不具有男性的陽剛之氣，無法修習怒海狂濤。\n");

        if ((int)me->query_skill("force", 1) < 150)
                return notify_fail("你的基本內功火候還不夠，還不能修煉怒海狂濤。\n");

        if (me->query_str() < 45)
                return notify_fail("你的膂力不足，難以修習怒海狂濤。\n");


        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("怒海狂濤只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"surge-force/" + func;
}