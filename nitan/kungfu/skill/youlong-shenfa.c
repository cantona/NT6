// youlong-shenfa.c 遊龍身法
// Last Modified by sir on 10.18.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "只見$n一招"HIC"「龍翔九天」"NOR"，右腳輕輕點地，身體「嗖」的向上筆直地縱起
丈余，躲過了$N這一招。\n",
        "$n一個"HIY"「龍遊四海」"NOR"，雙臂一張，行雲流水般向後縱出，避開了$N的凌厲
攻勢。\n",
        "$n使出"MAG"「翩若驚鴻」"NOR"，身形不住閃動，終于躲過$N的攻擊。\n",
        "$n使出"BLU"「神龍無影」"NOR"，$N眼前一花，已不見$n蹤影。\n",
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me) 
{              
        if( (int)me->query_skill("honghua-shengong", 1) < 10 )
        return notify_fail("你的紅花神功不夠精熟，無法領會遊龍身法。\n");
        return 1;
} 
int practice_skill(object me)
{
        if( query("qi", me)<30 || query("neili", me)<6 )
                return notify_fail("你的體力太差了，無法練習遊龍身法。\n");
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
        write(HIM"\n遊龍身法："NOR"\n");
        write(@HELP

    紅花會輕功身法。

        學習要求：
                紅花神功10級
HELP
        );
        return 1;
}