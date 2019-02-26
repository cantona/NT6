// tiannan-bu.c 天南步法

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
"只見$n一招"HIG"「旱地拔葱」"NOR"，身體向上筆直地縱起丈餘，躲過了$N這一招。\n",
"$n一個"MAG"「雨燕歸巢」"NOR"，向後縱出數丈之遠，避開了$N的凌厲攻勢。\n",
"$n使出"BLK"「破土而出」"NOR"，向一旁飄然縱出，輕輕着地。\n",
"但是$n身形飄忽，一招"BLU"「無中生有」"NOR"輕輕一縱，早已避開。\n",
"$n身隨意轉，一招"HIC"「乘風而去」"NOR"倏地往一旁挪開了三尺，避過了這一招。\n",
"可是$n側身一讓，一招"HIY"「鯀化大鵬」"NOR"$N這一招撲了個空。\n",
"卻見$n足不點地，一招"HIW"「青雲直上」"NOR"往旁竄開數尺，躲了開去。\n",
"$n身形微晃，一招"HIR"「鳳翔九天」"NOR"有驚無險地避開了$N這一招。\n",
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<20 || query("neili", me)<10 )
                return notify_fail("你的體力太差了，不能練天南步法。\n");
        me->receive_damage("qi", 20);
        addn("neili", -4, me);
        return 1;
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 20; }
int power_point(object me) { return 1.2; }

int help(object me)
{
        write(HIC"\n天南步法："NOR"\n");
        write(@HELP

    天南步法是天南大理段家本門輕功身法。

        學習要求：

HELP
        );
        return 1;
}
