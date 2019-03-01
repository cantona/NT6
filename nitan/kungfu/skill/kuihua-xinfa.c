// kuihua-xinfa.c 葵花心法
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit FORCE;

string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }
int valid_force(string force)
{
        return 1;
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("kuihua-xinfa", 1);
        return lvl * lvl * 15 * 10 / 100 / 200;
}

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int i = (int)me->query_skill("kuihua-xinfa", 1);
        int t = 1, j;
        if (i > 200) i = 200;
        for (j = 1; j < i / 10; j++) t*= 2;
        if ((int)me->query_skill("force", 1) < 10)
                return notify_fail("你的基本內功火候不足，不能學葵花心法。\n");
        if( i>10 && query("shen", me)>t*100 )
                return notify_fail("學葵花心法，要心狠手辣，姦惡歹毒，你可做得不夠呀！\n");
/*
        if ( me->query_skill("buddhism",1) || me->query_skill("taoism",1) )
                return notify_fail("你練了禿驢牛鼻子們的心法，還學葵花心法做什麼！\n");
*/
        if( query("gender", me) != "無性" && !query("special_skill/ghost", me) ) 
                return notify_fail("欲練神功，揮刀自宮！\n");

        return ::valid_learn(me);
}
int practice_skill(object me)
{
        return notify_fail("葵花心法只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"kuihua-xinfa/" + func;
}

int help(object me)
{
        write(HIC"\n葵花心法："NOR"\n");
        write(@HELP

    葵花心法為日月神教黑木崖本門內功心法。

        學習要求：
                基本內功10級
                相應的戾氣
                不能學禪宗心法和道家心法
HELP
        );
        return 1;
}
