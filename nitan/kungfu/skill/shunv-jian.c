//shunv-jian 淑女劍法
//modify by rcwiz 2003

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$N嬌喝一聲，手中$w劍光暴漲，指向$n$l",
        "force"  : 130,
        "attack" : 35,
        "parry"  : 20,
        "dodge"  : 40,
        "damage" : 100,
        "lvl"    : 0,
        "damage_type" : "刺傷"
]),
([      "action" : "$N手中$w反轉斜刺，劍法柔中帶剛，指向$n$l",
        "force"  : 150,
        "attack" : 45,
        "parry"  : 52,
        "dodge"  : 55,
        "damage" : 118,
        "lvl"    : 30,
        "damage_type" : "刺傷"
]),
([      "action" : "$N一聲嬌斥，劍勢陡快，手中$w斬向$n",
        "force"  : 190,
        "attack" : 81,
        "parry"  : 18,
        "dodge"  : 103,
        "damage" : 155,
        "lvl"    : 60,
        "damage_type" : "砍傷"
]),
([      "action" : "$N腰姿一擺，劍光突現，手中$w一退反進，刺向$n$l",
        "force"  : 250,
        "attack" : 108,
        "parry"  : 20,
        "dodge"  : 122,
        "damage" : 200,
        "lvl"    : 90,
        "damage_type" : "刺傷"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; } 

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力修為不夠，無法修習淑女劍法。\n");

        if ((int)me->query_skill("dodge", 1) < 40)
                return notify_fail("你的基本輕功火候太淺，無法修習淑女劍法。\n");

        if ((int)me->query_dex() < 24)
                return notify_fail("你的身法還不夠靈活，無法修習淑女劍法。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("shunv-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的淑女劍法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;

        level = (int) me->query_skill("shunv-jian",1);
        for (i = sizeof(action); i > 0; i--)
                    if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<45 )
                return notify_fail("你的體力不夠。\n");

        if( query("neili", me)<38 )
                return notify_fail("你的內力不夠。\n");

        me->receive_damage("qi", 40);
        addn("neili", -34, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"shunv-jian/" + action;
}