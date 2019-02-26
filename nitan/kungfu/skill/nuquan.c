// This program is a part of NITAN MudLIB

inherit SKILL;

mapping *action = ({
([      "action": "$N雙目赤紅，身帶沖天殺氣，招數緩慢凝重，一招「天地無光」似有千鈞之力，緩緩朝$n的$l處拍去",
        "force" : 130,
        "dodge" : -20,
        "parry" : -20,
        "attack": 15,
        "damage": 20,
        "lvl"   : 0,
        "skill_name" : "天地無光",
        "damage_type": "瘀傷"
]),
([      "action": "$N一聲長嘯．一招「毀天滅地」,一拳擊出，有遇天開天，遇地破地之威攻向$n",
        "force" : 185,
        "dodge" : -25,
        "parry" : -25,
        "attack": 17,
        "damage": 43,
        "lvl"   : 20,
        "skill_name" : "毀天滅地",
        "damage_type":  "瘀傷"
]),
([      "action": "$N的手掌不斷變換，一招「狂戰四野」幻化出數個形狀各異的掌形，頓時重重壓力攻向$n！",
        "force" : 220,
        "dodge" : -31,
        "parry" : -33,
        "attack": 21,
        "damage": 68,
        "lvl"   : 40,
        "skill_name" : "狂戰四野",
        "damage_type":  "內傷"
]),
([      "action": "$N立定身行，一招「同歸洪荒」，右拳再猛地揮出，這一拳之威彷彿充滿天地急速攻向$n！",
        "force" : 260,
        "dodge" : -71,
        "parry" : -83,
        "attack": 71,
        "damage": 88,
        "lvl"   : 90,
        "skill_name" : "同歸洪荒",
        "damage_type":  "內傷"
]),
});

int valid_enable(string usage) { return usage == "cuff" || usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練怒拳必須空手。\n");

        if ((int)me->query_skill("force") < 20)
                return notify_fail("你的內功火候不夠，無法學怒拳。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的內力太弱，無法練怒拳。\n");

        if ((int)me->query_skill("cuff", 1) < 20)
                return notify_fail("你的基本拳法火候太淺。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("nuquan", 1))
                return notify_fail("你的基本拳法水平有限，無法領會更高深的怒拳。\n");

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
        level = (int) me->query_skill("nuquan", 1);
        for (i = sizeof(action); i > 0; i--)
            if (level > action[i-1]["lvl"])
                return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<80 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練怒拳。\n");

        me->receive_damage("qi", 55);
        addn("neili", -45, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"nuquan/" + action;
}
