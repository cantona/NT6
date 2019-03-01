inherit SKILL;

mapping *action = ({
([      "action": "$N使一招「霹靂閃」，雙拳飛出，襲向$n$l",
        "force" : 130,
        "dodge" : 20,
        "parry" : 20,
        "attack": 15,
        "damage": 20,
        "lvl"   : 0,
        "skill_name" : "霹靂閃",
        "damage_type": "瘀傷"
]),
([      "action": "$N左右雙拳連環擊出，一招「天雷轟」，拳風驟響，襲向$n$l",
        "force" : 185,
        "dodge" : 25,
        "parry" : 25,
        "attack": 17,
        "damage": 43,
        "lvl"   : 20,
        "skill_name" : "天雷轟",
        "damage_type":  "瘀傷"
]),
([      "action": "$N左掌圈花揚起，屈肘當胸，右手虎口朝上，一招「天地絕」打向$n的",
        "force" : 220,
        "dodge" : 31,
        "parry" : 33,
        "attack": 21,
        "damage": 68,
        "lvl"   : 40,
        "skill_name" : "天地絕",
        "damage_type":  "內傷"
]),
});

int valid_enable(string usage) { return usage == "cuff" || usage == "parry"; }

/*
int valid_combine(string combo)
{
        return combo == "feihua-zhang";
}
*/

int valid_learn(object me)
{
        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail("練霹靂神拳必須空手。\n");

        if ((int)me->query_skill("force") < 20)
                return notify_fail("你的內功火候不夠，無法學霹靂神拳。\n");

        if ((int)query("max_neili", me) < 100)
                return notify_fail("你的內力太弱，無法練霹靂神拳。\n");

        if ((int)me->query_skill("cuff", 1) < 20)
                return notify_fail("你的基本拳法火候太淺。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("pili-quan", 1))
                return notify_fail("你的基本拳法水平有限，無法領會更高深的霹靂神拳。\n");

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
        level = (int) me->query_skill("pili-quan", 1);
        for (i = sizeof(action); i > 0; i--)
            if (level > action[i-1]["lvl"])
                return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        if ((int)query("qi", me) < 80)
                return notify_fail("你的體力太低了。\n");

        if ((int)query("neili", me) < 80)
                return notify_fail("你的內力不夠練霹靂神拳。\n");

        me->receive_damage("qi", 55);
        addn("neili", -45, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"pili-quan/" + action;
}