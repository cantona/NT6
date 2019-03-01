inherit FORCE;

int valid_enable(string usage)
{
            return usage == "force";
}

int valid_force(string force)
{
        return force == "yijinjing" ||
               force == "fenxin-jue";
}

int valid_learn(object me)
{
         
            return ::valid_learn(me);
}

int practice_skill(object me)
{
            return notify_fail("絕情心法只能用學(learn)的來增加熟練度。\n");
}
