inherit FORCE;

int valid_enable(string usage)
{
            return usage == "force";
}

int valid_force(string force)
{
        return force == "qingcheng-neigong" ||
               force == "changqing-shengong";
}

int valid_learn(object me)
{
            return ::valid_learn(me);
}

int practice_skill(object me)
{
            return notify_fail("青城內功只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
            return __DIR__"qingcheng-neigong/" + func;
}