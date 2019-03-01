// yipai-liangsan.c

#include <ansi.h>

inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "$N一掌拍向$n，沒有什麼章法",
        "force" : 400,
        "attack": -50,
        "dodge" : -50,
        "parry" : -50,
        "damage": -50,
        "lvl"   : 0,
        "damage_type" : "內傷"
]),
([      "action": "$N深深吸了一口氣，雙掌劃了一個圈子，緩緩拍向$n，掌力有如排山倒海一般",
        "force" : 700,
        "attack": 400,
        "dodge" : -20,
        "parry" : 30,
        "damage": 300,
        "lvl"   : 150,
        "damage_type" : "內傷"
]),
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練一拍兩散必須空手。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功火候不夠，不能強行修習一拍兩散。\n");

        if( query("max_neili", me)<2500 )
                return notify_fail("你的內力還不夠強，無法修習一拍兩散。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("yipai-liangsan", 1))
                return notify_fail("你的基本掌法火候水平有限，無法領會更高深的一拍兩散。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action); i > 0; i--)
                if (level >= action[i - 1]["lvl"])
                        return action[i - 1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("yipai-liangsan", 1);
        if (level < action[1]["lvl"])
                return action[0];

        return action[1];
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || 
            query_temp("secondary_weapon", me) )
                return notify_fail("你必須空手練習！\n");

        if( query("qi", me)<300 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的內力不夠練一拍兩散。\n");

        me->receive_damage("qi", 100);
        addn("neili", -100, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        if (damage_bonus < 100) return 0;

        if( query("jiali", me)<50 || query("neili", me)<300 )
                return 0;

        me->start_busy(2);
        victim->receive_damage("qi", damage_bonus, me);
        if( query("neili", victim)<200 )
                set("neili", 0, victim);
        else
                addn("neili", -100, victim);

        return HIR "$n" HIR "接下$N這一掌，一時間只覺得渾身乏力。\n" NOR;
}
