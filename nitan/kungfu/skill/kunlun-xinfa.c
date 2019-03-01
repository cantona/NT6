// kunlun-xinfa.c 昆侖心法

inherit FORCE;

int valid_enable(string usage)
{
            return usage == "force";
}

int valid_force(string force)
{
        return force == "kunlun-xinfa" ||
               force == "liangyi-shengong";
}

int valid_learn(object me)
{
            return ::valid_learn(me);
}

int practice_skill(object me)
{
            return notify_fail("昆侖心法只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
            return __DIR__"kunlun-xinfa/" + func;
}