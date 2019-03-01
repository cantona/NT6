// xueshan-neigong.c 雪山內功

inherit FORCE;

int valid_enable(string usage)
{
            return usage == "force";
}

int valid_force(string force)
{
        return 1;
        return force == "xueshan-neigong" ||
               force == "wuwang-shengong";
}

int valid_learn(object me)
{
            return ::valid_learn(me);
}

int practice_skill(object me)
{
            return notify_fail("雪山內功只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
            return __DIR__"xueshan-neigong/" + func;
}