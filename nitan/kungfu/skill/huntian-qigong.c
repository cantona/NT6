// huntian-qigong.c 混天氣功

#include <ansi.h>;

inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }

int valid_force(string force)
{
        return 1;
        return force == "jiaohua-neigong";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("huntian-qigong", 1);
        return lvl * lvl * 15 * 9 / 100 / 200;
}
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        if (me->query_skill("force", 1) < 30)
                return notify_fail("你的基本內功火候不夠，無法學習混天氣功。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("混天氣功只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"huntian-qigong/" + func;
}

int help(object me)
{
        write(HIC"\n混天氣功："NOR"\n");
        write(@HELP

    混天氣功為丐幫本門內功。

        學習要求：
                學混天氣功，要不正不邪、亦正亦邪
HELP
        );
        return 1;
}
