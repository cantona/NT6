// ding-force.c 小丁氣功

inherit FORCE;

int valid_force(string force) { return 1; }

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("ding-force", 1);
        return lvl * lvl * 19 * 15 / 100 / 200;
}

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        if( query("gender", me) == "無性" && me->query_skill("ding-force",1)>49 )
                return notify_fail("公公無根無性，小丁氣功再難更上一層樓。\n");
        return 1;
}

int practice_skill(object me)
{
        return notify_fail("小丁氣功只能跟小丁學來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"ding-force/" + func;
}


