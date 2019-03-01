// huiyan-xinfa.c 回雁心法
// Last Modified by ahda on Aug.30 2001

#include <ansi.h>;
#include "force.h";
inherit FORCE;

string type() { return "martial"; }
string martialtype() { return "force"; }
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("huiyan-xinfa", 1);
        int t = 1, j;
        if (lvl<=100)
                for (j = 1; j < lvl / 10; j++)
                        t*=2;

        if( query("gender", me) == "無性" && lvl>49 )
                return notify_fail("你無根無性，陰陽不調，難以領會高深的回雁心法。\n");

        if ((int)me->query_skill("force", 1) < 10)
                return notify_fail("你的基本內功火候還不夠。\n");

        if(lvl<=100)
        {
                if( lvl>10 && query("shen", me)<t*100 )
                        return notify_fail("你的俠義正氣太低了，無法領會更高深的回雁心法。\n");
        }
        else
        {
                if( query("shen", me)<(51200+(lvl-100)*1000) )
                        return notify_fail("你的俠義正氣太低了，無法領會更高深的回雁心法。\n");
        }

        return valid_public(me);
}

int practice_skill(object me)
{
        return notify_fail("回雁心法只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"huiyan-xinfa/" + func;
}

int help(object me)
{
        write(HIC"\n回雁心法："NOR"\n");
        write(@HELP

    回雁心法乃衡山派鎮山武學，為衡山派前輩高人所創，是
    修習衡山派各種高深武功的根基，有延年益壽之功效。

        學習要求：
                基本內功10級
                相應的正氣
                太監無法領悟50級以上的回雁心法
HELP
        );
        return 1;
}
