// quanzhen-xinfa 全真心法

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return 1;
        return force == "xiantian-gong" ||
               force == "xuanmen-neigong";
}

int valid_learn(object me)
{
        return 1;
}

int practice_skill(object me)
{
        return notify_fail("全真心法只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"quanzhen-xinfa/" + func;
}