// fengshenjue.c  風神訣
// Last Modified by sir on 10.18.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "只見$n使出" HIC"「洛神凌波」"NOR"，衣訣飄飄，腳下如凌波踏水，快速幾步，已避開攻擊。\n",
        "但是$n使出" HIW"「凌空虛度」"NOR"，提氣縱起，在空中連跨七步，已在$N尋丈之外。\n",
        "$n一招"HIY"「布法行雲」"NOR"，腳踏子午，掌分陰陽，不經意間避過$N這一招。\n",
        "可是$n一個" HIC"「風起雲湧」"NOR"，身形如被大風所吹，飄飄優悠落到$N身後。\n",
        "卻見$n使出" GRN"「春風拂柳」"NOR"，一足腳尖點地，身如弱柳，俯仰不定，$N這招可落了空。\n",
        "$n使出"YEL "「秋風蕭瑟」"NOR"，一手捂胸，挺身前行，大有壯士一去不復返之勢，$N被其氣勢所懾，只得退開。\n",
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me) 
{              
        if( (int)me->query_skill("panshi-shengong", 1) < 10 )
        return notify_fail("你的磐石神功不夠精熟，無法領會風神訣。\n");
        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<30 || query("neili", me)<6 )
                return notify_fail("你的體力太差了，無法練習風神訣。\n");
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
        write(HIC"\n風神訣："NOR"\n");
        write(@HELP

    泰山派的輕功身法。

        學習要求：
           磐石神功10級
HELP
        );
        return 1;
}
