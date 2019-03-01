// juemen-gun.c 絕門棍
// Last Modified by sega on Mar. 10 2000
//沒碰文件,沒用吧?
//歸雲莊南西仁和柯鎮惡用著個？

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *dodge_msg = ({
        "$n右腳輕輕一點躍開躲過了$N的攻擊。\n",
        "$n向旁邊撲出，順勢一滾，閃到一邊。\n",
        "$n斜裡沖前一步，身法詭異，$N這一招落到空處。\n",
        "$n忽然直身飛入半空，很久也不見人影，半響後竟閃到了$N的背後。\n",
        "$n突然一個急轉身，$N的這一招滑到了一邊。\n",
});

mapping *action = ({
([        "action" : "$N斜裡沖前一步，身法詭異，手中$w橫掃$n的$l",
        "damage": 450,
        "dodge" : 50,
        "damage_type" : "挫傷"
]),
([        "action" : "$N忽然直身飛入半空，很久也不見人影，$n正搜尋間，$N已
飛身撲下，$w攻向$n的$l",
        "damage": 500,
        "dodge" : 45,
        "damage_type" : "挫傷"
]),
([        "action" : "$N原地一個後滾翻，卻在落地的一剎那，身體向$n平飛過
去，手中$w指向$n的$l",
        "damage": 550,
        "dodge" : 60,
        "damage_type" : "挫傷"
]),
([        "action" : "$N突然一個急轉身，$w橫掃一圈後挾著猛烈的勁道打向$n的$l",
        "damage": 600,
        "dodge" : 75,
        "damage_type" : "挫傷"
]),
([        "action" : "$N向前撲出，順勢一滾，接著翻身跳起，手裡$w斜向上擊
向$n的$l",
        "damage": 750,
        "dodge" : 65,
        "damage_type" : "挫傷"
]),
([        "action" : "$N手中$w上下翻飛，舞成了一團杖花，這杖花繞$n遊走三
圈後指向$n的$l",
        "damage": 800,
        "dodge" : 65,
        "damage_type" : "挫傷"
])
});

int valid_enable(string usage){return usage=="club" || usage=="parry"|| usage=="dodge"; }

int valid_learn(object me)
{
    if( query("max_neili", me)<200 )
        return notify_fail("你的內力太弱，無法練絕門棍。\n");

    if ((int)me->query_dex() < 23)
        return notify_fail("你的身法不夠靈活，無法練絕門棍。\n");

    return 1;
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
    if( query("qi", me)<60 )
        return notify_fail("你的體力太低了。\n");

    if( query("neili", me)<50 )
        return notify_fail("你的內力不夠練絕門棍。\n");

    me->receive_damage("qi", 45);
    addn("neili", -38, me);
    return 1;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point() { return 1.0; }
int valid_effect(object me, object weapon, string name, int skill)
{
}
string perform_action_file(string action)
{
        return __DIR__"juemen-gun/" + action;
}

int help(object me)
{
        write(HIC"\n絕門棍："NOR"\n");
        write(@HELP

    絕門棍為少林七十二絕技之一。

        學習要求：
                混元一氣功20級
                內力400
HELP
        );
        return 1;
}
