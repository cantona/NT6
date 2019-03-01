// shennong-xinjing.c 神農心經

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return force == "shennong-xinjing" ||
               force == "yaogu-xinfa" ||
               force == "lengyue-shengong" ||
               force == "hujia-neigong" ||
               force == "danyang-tunafa" ||
               force == "miaojia-neigong" ;
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("shennong-xinjing", 1);
                return lvl * lvl * 15 * 21 / 100 / 200;
}

int valid_learn(object me)
{
        if( query("gender", me) == "無性" && me->query_skill("shennong-xinjing",1)>99 )
                return notify_fail("你無根無性，陰陽不調，難以領會高深的神農心經。\n");

        if ((int)me->query_skill("force", 1) < 60)
                return notify_fail("你的基本內功火候還不夠。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("神農心經只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"shennong-xinjing/" + func;
}