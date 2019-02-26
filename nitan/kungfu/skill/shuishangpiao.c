// shuishangpiao.c 鐵掌水上飄
// Last Modified by sir on 10.18.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
"$n足跟一支，全身後仰，一招"BLU"「鯉魚倒穿波」"NOR"，反竄出丈餘，躲過了$N的攻擊。\n",
"$n身體忽然柔若無骨，左右搖擺，使出一招"BLU"「雨打漂萍」"NOR"，避過了$N的攻擊。\n",
"$n使出"HIB"「物換星移」"NOR"，滴溜溜一個轉身，從$N身旁擦身而過，反而到了$N身後。\n",
"$n一招"HIY"「落葉隨風」"NOR"，身體如一片落葉一般飄了出去，身行之瀟灑，迅速到了極處。\n",
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me) 
{              
        if( (int)me->query_skill("guiyuan-tunafa", 1) < 10 )
        return notify_fail("你的歸元吐納法不夠精熟，無法領會鐵掌水上飄。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<30 || query("neili", me)<6 )
                return notify_fail("你的體力太差了，無法練習鐵掌水上飄。\n");
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
int river_point() {return 1.5;} // 過河比普通容易 越高越好
string river_go_msg() {        return HIW"$N飛身躍在水面，身形穩凝，河水只及小腿，一步步走了過去。\n"NOR;}
string river_come_msg() {        return HIW"只見水面上人影閃動，$N如飄在上面一般，直走過來。\n"NOR;}

int help(object me)
{
        write(HIC"\n鐵掌水上飄："NOR"\n");
        write(@HELP

    鐵掌幫的獨門輕功身法。

        學習要求：
          歸元吐納法10級
HELP
        );
        return 1;
}
