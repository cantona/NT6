// qiuyan-nanhui.c 秋雁南迴
// Last Modified by sir on 10.18.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "$n一式"CYN"「雁渡寒潭」"NOR"，身不傾，腳不移，身體如行雲流水般直滑出丈餘。\n",
        "$n一式"CYN"「平沙落雁」"NOR"，忽然一彎腰，全身貼地而行，頓時閃過了$N的凌厲攻勢。\n",
        "$n一式"CYN"「雁舞風堂」"NOR"，一轉身間，四面八方飄動着無數個$n的身影，令$N手足無措。\n",
        "$n一式"CYN"「雲雁驚厥」"NOR"，長袖一拂，全身化為一道白影，幽幽地從$N頭頂飄落。\n",
        "$n一式"CYN"「雁影行洲」"NOR"，身體如陀螺般急轉，登時一股氣流湧出，令$N難以動彈。\n",
});


int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me) 
{              
        if( (int)me->query_skill("huiyan-xinfa", 1) < 10 )
        return notify_fail("你的回雁心法不夠精熟，無法領會秋雁南迴。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<30 || query("neili", me)<6 )
                return notify_fail("你的體力太差了，無法練習秋雁南迴。\n");
        me->receive_damage("qi", 30);
        addn("neili", -6, me);
        return 1;
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.3; }

int help(object me)
{
        write(HIC"\n秋雁南迴："NOR"\n");
        write(@HELP

    衡山派的輕功身法。

        學習要求：
           回雁心法10級
HELP
        );
        return 1;
}
