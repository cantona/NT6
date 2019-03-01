inherit SKILL;

mapping *action = ({
([      "action": "$N使出一招「力拔山河」，左掌虛晃一下，右手帶起陣陣掌風拍向$n的$l",
        "force" : 100,
        "attack": 18,
        "dodge" : 30,
        "parry" : 15,
        "damage": 40,
        "lvl"   : 0,
        "damage_type": "瘀傷",
        "skill_name" : "力拔山河",
]),
([      "action": "$N縱身躍起，一式「開碑斷石」，雙掌自上而下拍向$n的$l",
        "force" : 200,
        "attack": 25,
        "dodge" : 40,
        "parry" : 30,
        "damage": 45,
        "lvl"   : 30,
        "damage_type": "瘀傷",
        "skill_name" : "開碑斷石",
]),
([      "action": "$N雙掌呼地拍出，一招「風雨欲來」，帶起陣陣飛沙走石，直擊向$n的$l",
        "force" : 250,
        "attack": 35,
        "dodge" : 50,
        "parry" : 55,
        "damage": 45,
        "lvl"   : 60,
        "damage_type": "瘀傷",
        "skill_name" : "風雨欲來",
]),
([      "action": "$N雙掌齊出，幻做掌影重重，一招「地老天荒」拍向$n$l",
        "force" : 290,
        "attack": 42,
        "dodge" : 70,
        "parry" : 75,
        "damage": 43,
        "lvl"   : 120,
        "damage_type": "瘀傷",
        "skill_name" : "地老天荒",
]),
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

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
        level = (int)me->query_skill("zhenshan-zhang", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練震山掌必須空手。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，無法練震山掌。\n");

        if( query("max_neili", me)<450 )
                return notify_fail("你的內力太弱，無法練震山掌。\n");

        if (me->query_skill("strike", 1) < me->query_skill("zhenshan-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的震山掌。\n");

        return 1;
}


int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("你的體力太低了，先休息一下吧。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練震山掌。\n");

        if (me->query_skill("zhenshan-zhang", 1) < 50)
                me->receive_damage("qi", 30);
        else
                me->receive_damage("qi", 50);

        addn("neili", -54, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"zhenshan-zhang/" + action;
}
