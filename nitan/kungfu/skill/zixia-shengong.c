// zixia-shengong.c 紫霞神功

#include <ansi.h>;
inherit FORCE;

string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point() { return 1; }
int valid_force(string force)
{
        return 1;
}

int query_neili_improve(object me)
{
        int lvl;
        lvl = (int)me->query_skill("zixia-shengong", 1);
        return lvl * lvl * 20 * 15 / 100 / 200;
}

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int i, t, level;

        level = (int)me->query_skill("zixia-shengong", 1);

        if (level <= 100)
                for (i = 1; i < level / 10; i++)
                        t *= 2;

        if( query("gender", me) == "無性" && level>49 )
                return notify_fail("公公無根無性，紫霞神功再難更上一層樓。\n");

        if ((int)me->query_skill("zixia-shengong", 1) >= 45
        &&  (int)me->query_skill("huagong-dafa", 1) >= 100
        &&  (int)me->query_int() < 100 )
                return notify_fail("你受高深的邪派內功牽絆，與紫霞神功水火難容，以你的智商再難更上一層樓。\n");

        if (level <= 100)
        {
                if( level>10 && query("shen", me)<t*100 )
                        return notify_fail("你的俠義正氣太低了，無法領會更高深的紫霞神功。\n");
        }
        else
        {
                if( query("shen", me)<(51200+(level-100)*1000) )
                        return notify_fail("你的俠義正氣太低了，無法領會更高深的紫霞神功。\n");
        }
        return ::valid_learn(me);
}


int practice_skill(object me)
{
        return notify_fail("紫霞神功只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"zixia-shengong/" + func;
}
int help(object me)
{
        write(HIM"\n紫霞神功："NOR"\n");
        write(@HELP

    華山氣宗內功，具自療及運功之用，並能增加精氣。精的增加
視乎於自身紫氤吟的修為，氣的增加則決定於自身正氣訣的修為。

        學習要求：
                基本內功10級
                相應的正氣
                太監無法學到50級以上的紫霞神功
HELP
        );
        return 1;
}
