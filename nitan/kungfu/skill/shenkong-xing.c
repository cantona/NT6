// shenkong-xing.c 身空行

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "$n使出一招"HIC"「心空」"NOR"，身體向側後飄去 \n",
        "$n使出一招"HIW"「誓言空」"NOR"，雙足一點，躍至數丈之外 \n",
        "$n使出一招"HIM"「蓮空」"NOR"，身形一變，滑至$N身後 \n",
        "$n大吼一聲，使出一招"HIG"「大安空」"NOR"，從$N頭頂越過 \n",
        "$n使出一招"HIY"「佛空」"NOR"，如輕鴻般飄去，瞬間又閃至$N面前 \n",
        "$n使出一招"HIR"「金剛空」"NOR"，頓時$N周圍都是$n的身影 \n",
});

int valid_enable(string usage) { return usage == "dodge" || usage == "move"; }
int valid_learn(object me)
{
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<10 || query("neili", me)<2 )
                return notify_fail("你的體力太差了，不能練身空行。\n");
        me->receive_damage("qi", 10);
        addn("neili", -4, me);
        return 1;
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int learn_bonus() { return 25; }
int practice_bonus() { return 25; }
int success() { return 20; }
int power_point(object me) { return 1.1; }

int help(object me)
{
        write(HIC"\n身空行："NOR"\n");
        write(@HELP

    身空行是雪山寺弟子本門輕功身法。

        學習要求：
HELP
        );
        return 1;
}
