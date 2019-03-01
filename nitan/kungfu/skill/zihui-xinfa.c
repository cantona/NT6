// zihui-xinfa 紫徽心法

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
//        return force == "murong-xinfa";
        return 1;
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("zihui-xinfa", 1);
                return lvl * lvl * 15 * 18 / 100 / 200;
}

int valid_learn(object me)
{
        if( query("gender", me) == "無性" && me->query_skill("zihui-xinfa",1)>49 )
                return notify_fail("你無根無性，陰陽不調，難以領會更高深的紫徽心法。\n");

        if ((int)me->query_skill("force", 1) < 20)
                return notify_fail("你的基本內功火候還不夠，還不能學習紫徽心法。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("紫徽心法只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"zihui-xinfa/" + func;
}
