inherit SKILL;

mapping *action = ({
([      "action" : "$N一招「千錘百煉」，單掌平勢緩推而出，陡然拍向$n的$l",
        "force"  : 33,
        "dodge"  : 5,
        "parry"  : 2,
        "attack" : 2,
        "damage" : 1,
        "lvl"    : 0,
        "skill_name" : "千錘百煉",
        "damage_type": "瘀傷"
]),
([      "action" : "$N使一招「旁敲側擊」，右手劃了一個圈子，左手揮劈$n而去",
        "force"  : 45,
        "dodge"  : 18,
        "parry"  : 17,
        "attack" : 6,
        "damage" : 4,
        "lvl"    : 20,
        "skill_name" : "旁敲側擊",
        "damage_type": "瘀傷"
]),
([      "action" : "$N右手由鈎變掌，使一招「力拔千鈞」，單掌登時橫掃$n的$l",
        "force"  : 51,
        "dodge"  : 16,
        "parry"  : 19,
        "attack" : 11,
        "damage" : 7,
        "lvl"    : 40,
        "skill_name" : "力拔千鈞",
        "damage_type": "瘀傷"
]),
([      "action" : "$N雙手劃弧，雙掌輪番拍出，使一招「威震八方」砍向$n的面門",
        "force"  : 62,
        "dodge"  : 24,
        "parry"  : 21,
        "attack" : 15,
        "damage" : 9,
        "lvl"    : 60,
        "skill_name" : "威震八方",
        "damage_type": "瘀傷"
]),
});

int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_combine(string combo)
{
        return combo == "jueming-tui";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練銅錘掌法必須空手。\n");

        if ((int)me->query_skill("force") < 15)
                return notify_fail("你的內功火候不夠，無法學銅錘掌法。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的內力修為太弱，無法練銅錘掌法。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("tongchui-zhang", 1))
                return notify_fail("你的基本掌法火候不足，無法領會更高深的銅錘掌法。\n");

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
        level = (int) me->query_skill("tongchui-zhang", 1);
        for (i = sizeof(action); i > 0; i--)
            if (level > action[i-1]["lvl"])
                return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("你現在手足痠軟，休息一下再練吧。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠練銅錘掌法。\n");

        me->receive_damage("qi", 48);
        addn("neili", -42, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tongchui-zhang/" + action;
}