// guixi-gong.c

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return 1;
    return force == "huagong-dafa";
}

int valid_learn(object me)
{
        return 1;
}

int practice_skill(object me)
{
        return notify_fail("龜息功只能用學(learn)的來增加熟練度。\n");
}