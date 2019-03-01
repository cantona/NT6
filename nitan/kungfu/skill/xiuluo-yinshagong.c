// xiuluo-yinshagong.c 修羅陰煞功

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return force == "wudu-xinfa" ||
               force == "hamagong" ||
               force == "shunxi-qianli";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("xiuluo-yinshagong", 1);
                return lvl * lvl * 15 * 10 / 100 / 200;
}

int valid_learn(object me)
{
        if( query("gender", me) == "無性" && me->query_skill("xiuluo-yinshagong",1)>49 )
                return notify_fail("你無根無性，陰陽不調，難以領會高深的修羅陰煞功。\n");

        if ((int)me->query_skill("force", 1) < 60)
                return notify_fail("你的基本內功火候還不夠。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("修羅陰煞功只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"xiuluo-yinshagong/" + func;
}