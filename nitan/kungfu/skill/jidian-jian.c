#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$N縱身躍起手中$w輕揮，一招「風平浪靜」，斬向$n後頸",
        "force"  : 80,
        "attack" : 35,
        "parry"  : 10,
        "dodge"  : 30,
        "damage" : 75,
        "lvl"    : 0,
        "skill_name" : "風平浪靜",
        "damage_type" : "刺傷"
]),
([      "action" : "$N手中$w連話三個弧形，一招「風起雲湧」，向$n的右臂齊肩斬落",
        "force"  : 100,
        "attack" : 45,
        "parry"  : 22,
        "dodge"  : 45,
        "damage" : 88,
        "lvl"    : 30,
        "skill_name" : "風起雲湧",
        "damage_type" : "刺傷"
]),
([      "action" : "$N輕吁一聲，飛身一躍而起，一招「風卷殘雲」，連續向$n刺出數劍",
        "force"  : 120,
        "attack" : 51,
        "parry"  : 18,
        "dodge"  : 53,
        "damage" : 95,
        "lvl"    : 60,
        "skill_name" : "風卷殘雲",
        "damage_type" : "刺傷"
]),
([      "action" : "$N仰天一聲清嘯，斜行向前，一招「風流雲散」，$w橫削直擊，擊向$n的$l",
        "force"  : 150,
        "attack" : 58,
        "parry"  : 20,
        "dodge"  : 52,
        "damage" : 110,
        "lvl"    : 90,
        "skill_name" : "風流雲散",
        "damage_type" : "割傷"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; } 

int valid_learn(object me)
{
        if( query("max_neili", me)<200 )
                return notify_fail("你的內力不夠，無法修習疾電劍法。\n");

        if ((int)me->query_skill("dodge") < 60)
                return notify_fail("你的輕功火候太淺，無法修習疾電劍法。\n");

        if ((int)me->query_dex() < 25)
                return notify_fail("你的身法還不夠靈活，無法修習疾電劍法。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("jidian-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的疾電劍法。\n");

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

        level = (int) me->query_skill("jidian-jian",1);
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

        if( query("qi", me)<65 )
                return notify_fail("你的體力不夠練疾電劍法。\n");

        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練疾電劍法。\n");

        me->receive_damage("qi", 60);
        addn("neili", -16, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"jidian-jian/" + action;
}