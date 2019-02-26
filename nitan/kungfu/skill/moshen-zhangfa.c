// This program is a part of NITAN MudLIB

inherit SKILL;

mapping *action = ({
([      "action": "$N右手冒出陣陣寒氣，劃了一個弧線朝$n的$l處打去",
        "force" : 10,
        "dodge" : 5,
        "parry" : 2,
        "lvl"   : 0,
        "skill_name" : "蒼松迎客",
        "damage_type": "瘀傷"
]),
([      "action": "$N掌中的真氣呈氣勁，猛地朝$n的$l處擊去",
        "force" : 15,
        "dodge" : 18,
        "parry" : 17,
        "lvl"   : 10,
        "skill_name" : "峯迴路轉",
        "damage_type": "瘀傷"
]),
([      "action": "$N手掌一翻，雙手掌重疊，只見一股氣勁朝$n的$l處激射過去",
        "force" : 15,
        "dodge" : 16,
        "parry" : 19,
        "lvl"   : 20,
        "skill_name" : "奇峯突現",
        "damage_type": "瘀傷"
]),
([      "action": "$N雙掌平推，$n只覺得一股翻江倒海之力朝自己壓來",
        "force" : 25,
        "dodge" : 24,
        "parry" : 21,
        "lvl"   : 30,
        "skill_name" : "漫天花舞",
        "damage_type": "瘀傷"
]),

});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練魔神掌法必須空手。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功火候不夠，無法學魔神掌法。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的內力太弱，無法練魔神掌法。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("moshen-zhangfa", 1))
                return notify_fail("你的基本掌法火候不足，無法領會更高深的魔神掌法。\n");

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
        level = (int) me->query_skill("moshen-zhangfa", 1);
        for (i = sizeof(action); i > 0; i--)
            if (level > action[i-1]["lvl"])
                return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<100 )
                return notify_fail("你現在手足痠軟，休息一下再練吧。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠了。\n");

        me->receive_damage("qi", 80);
        addn("neili", -50, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"moshen-zhangfa/" + action;
}