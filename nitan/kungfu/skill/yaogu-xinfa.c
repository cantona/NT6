// yaogu-xinfa.c 藥谷心法

inherit FORCE;

int valid_enable(string usage)
{
            return usage == "force";
}

int valid_force(string force)
{
        return force == "shennong-xinjing" ||
               force == "yaogu-xinfa" ||
               force == "lengyue-shengong" ||
               force == "hujia-neigong" ||
               force == "danyang-tunafa" ||
               force == "miaojia-neigong" ;
}

int valid_learn(object me)
{
            return ::valid_learn(me);
}

int practice_skill(object me)
{
            return notify_fail("藥谷心法只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
            return __DIR__"yaogu-xinfa/" + func;
}