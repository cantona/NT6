inherit SKILL;

mapping *action = ({
([      "action": "$N馬步一立，身子微曲，暗喝一聲，一招「望月拜天」，一拳直捅$n的$l",
        "force" : 30,
        "dodge" : 5,
        "parry" : 7,
        "attack": 4,
        "damage": 4,
        "lvl"   : 0,
        "skill_name" : "望月拜天",
        "damage_type": "瘀傷"
]),
([      "action": "$N哈哈一笑，左拳由下至上，右拳平平擊出，一招「跨日向天」，交替打向$n",
        "force" : 45,
        "dodge" : 18,
        "parry" : 17,
        "attack": 6,
        "damage": 6,
        "lvl"   : 20,
        "skill_name" : "跨日向天",
        "damage_type": "瘀傷"
]),
([      "action": "$N對$n一聲大喝，使一招「長虹經天」，左拳擊出，隨即右拳跟上，兩重力道打向$n的$l",
        "force" : 57,
        "dodge" : 16,
        "parry" : 19,
        "attack": 7,
        "damage": 11,
        "lvl"   : 40,
        "skill_name" : "長虹經天",
        "damage_type": "瘀傷"
]),
([      "action": "$N悶喝一聲，雙拳向上分開，一記「舉火燒天」，拳劃弧線，左右同時擊向$n的$l",
        "force" : 65,
        "dodge" : 24,
        "parry" : 21,
        "attack": 9,
        "damage": 14,
        "lvl"   : 60,
        "skill_name" : "舉火燒天",
        "damage_type": "瘀傷"
]),
([      "action": "$N施出「一臂擎天」，一聲大吼，一拳凌空打出，拳風直逼$n的$l",
        "force" : 85,
        "dodge" : 24,
        "parry" : 28,
        "attack": 13,
        "damage": 19,
        "lvl"   : 80,
        "skill_name" : "一臂擎天",
        "damage_type": "瘀傷"
]),
([      "action": "$N一聲長嘯，雙拳交錯擊出，一招「石破天驚」，拳風密佈$n的前後左右",
        "force" : 97,
        "dodge" : 28,
        "parry" : 30,
        "attack": 16,
        "damage": 21,
        "lvl"   : 100,
        "skill_name" : "石破天驚",
        "damage_type": "瘀傷"
]),
([      "action": "$N怒吼一聲，凌空飛起，一式「天崩地裂」，雙拳居高臨下，齊齊捶向$n",
        "force" : 115,
        "dodge" : 24,
        "parry" : 21,
        "attack": 17,
        "damage": 24,
        "lvl"   : 120,
        "skill_name" : "天崩地裂",
        "damage_type": "瘀傷"
]),
([      "action": "$N仰天大笑，勢若瘋狂，衣袍飛舞，一招「無法無天」，拳風凌厲，如雨點般向$n打去",
        "force" : 135,
        "dodge" : 26,
        "parry" : 25,
        "attack": 23,
        "damage": 28,
        "lvl"   : 140,
        "skill_name" : "無法無天",
        "damage_type": "瘀傷"
]),
});

int valid_enable(string usage) { return usage == "cuff" || usage == "parry"; }

int valid_combine(string combo)
{
        return combo == "kunlun-zhang" || combo == "sanyin-shou";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練震天拳必須空手。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功火候不夠，無法學震天拳。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的內力太弱，無法練震天拳。\n");

        if ((int)me->query_skill("cuff", 1) < 20)
                return notify_fail("你的基本拳法火候太淺。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("zhentian-quan", 1))
                return notify_fail("你的基本拳法水平有限，無法領會更高深的震天拳。\n");

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
        level = (int) me->query_skill("zhentian-quan", 1);
        for (i = sizeof(action); i > 0; i--)
            if (level > action[i-1]["lvl"])
                return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<80 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練震天拳法。\n");

        me->receive_damage("qi", 55);
        addn("neili", -45, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"zhentian-quan/" + action;
}