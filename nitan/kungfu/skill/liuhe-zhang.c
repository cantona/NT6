inherit SKILL;

mapping *action = ({
([      "action" : "$N一招「正掌還經」，單掌平勢緩推而出，陡然拍向$n的$l",
        "force"  : 33,
        "dodge"  : 5,
        "parry"  : 2,
        "attack" : 2,
        "damage" : 1,
        "lvl"    : 0,
        "skill_name" : "正掌還經",
        "damage_type": "瘀傷"
]),
([      "action" : "$N使一招「合掌擎天」，右手劃了一個圈子，左手揮出，劈向$n的$l",
        "force"  : 45,
        "dodge"  : 18,
        "parry"  : 17,
        "attack" : 6,
        "damage" : 4,
        "lvl"    : 20,
        "skill_name" : "合掌擎天",
        "damage_type": "瘀傷"
]),
([      "action" : "$N右手由鈎變掌，使一招「切掌現影」，單掌登時橫掃$n的$l",
        "force"  : 51,
        "dodge"  : 16,
        "parry"  : 19,
        "attack" : 11,
        "damage" : 7,
        "lvl"    : 40,
        "skill_name" : "切掌現影",
        "damage_type": "瘀傷"
]),
([      "action" : "$N雙手劃弧，右手向上，左手向下，使一招「翻掌劈山」砍向$n的面門",
        "force"  : 62,
        "dodge"  : 24,
        "parry"  : 21,
        "attack" : 15,
        "damage" : 9,
        "lvl"    : 60,
        "skill_name" : "翻掌劈山",
        "damage_type": "瘀傷"
]),
([      "action" : "$N左手劃了一個大圈，使一招「穿掌行柳」，擊向$n的$l",
        "force"  : 75,
        "dodge"  : 24,
        "parry"  : 28,
        "attack" : 19,
        "damage" : 11,
        "lvl"    : 80,
        "skill_name" : "穿掌行柳",
        "damage_type": "瘀傷"
]),
([      "action" : "$N雙手合掌，使一招「引掌開峯」，雙掌分別向$n的$l打去",
        "force"  : 90,
        "dodge"  : 28,
        "parry"  : 30,
        "attack" : 21,
        "damage" : 14,
        "lvl"    : 100,
        "skill_name" : "引掌開峯",
        "damage_type": "瘀傷"
]),
});

int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練六合掌法必須空手。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功火候不夠，無法學六合掌法。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的內力太弱，無法練六合掌法。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("liuhe-zhang", 1))
                return notify_fail("你的基本掌法火候不足，無法領會更高深的六合掌法。\n");

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
        level = (int) me->query_skill("liuhe-zhang", 1);
        for (i = sizeof(action); i > 0; i--)
            if (level > action[i-1]["lvl"])
                return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("你現在手足痠軟，休息一下再練吧。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠練六合掌法。\n");

        me->receive_damage("qi", 48);
        addn("neili", -42, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"liuhe-zhang/" + action;
}