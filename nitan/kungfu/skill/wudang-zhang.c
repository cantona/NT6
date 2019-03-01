inherit SKILL;

mapping *action = ({
([      "action": "$N一招「蒼鬆迎客」，單掌平推，拍向$n的$l",
        "force" : 10,
        "dodge" : 5,
        "parry" : 2,
        "lvl"   : 0,
        "skill_name" : "蒼鬆迎客",
        "damage_type": "瘀傷"
]),
([      "action": "$N使一招「峰回路轉」，右手劃了一個圈子，左手揮出，劈向$n的$l",
        "force" : 15,
        "dodge" : 18,
        "parry" : 17,
        "lvl"   : 10,
        "skill_name" : "峰回路轉",
        "damage_type": "瘀傷"
]),
([      "action": "$N右手由鉤變掌，使一招「奇峰突現」，橫掃$n的$l",
        "force" : 15,
        "dodge" : 16,
        "parry" : 19,
        "lvl"   : 20,
        "skill_name" : "奇峰突現",
        "damage_type": "瘀傷"
]),
([      "action": "$N雙手劃弧，右手向上，左手向下，使一招「白鶴亮翅」，分擊$n的面門和$l",
        "force" : 25,
        "dodge" : 24,
        "parry" : 21,
        "lvl"   : 30,
        "skill_name" : "白鶴亮翅",
        "damage_type": "瘀傷"
]),
([      "action": "$N左手劃了一個大圈，使一招「五行柳變」，擊向$n的$l",
        "force" : 25,
        "dodge" : 24,
        "parry" : 28,
        "lvl"   : 40,
        "skill_name" : "五行柳變",
        "damage_type": "瘀傷"
]),
([      "action": "$N雙手合掌，使一招「靈猴採桃」，雙掌分別向$n的$l打去",
        "force" : 30,
        "dodge" : 28,
        "parry" : 30,
        "lvl"   : 50,
        "skill_name" : "靈猴採桃",
        "damage_type": "瘀傷"
]),
([      "action": "$N左手橫于胸前，右掌直擊$n的$l，正是一招「仙人指路」",
        "force" : 35,
        "dodge" : 24,
        "parry" : 21,
        "lvl"   : 60,
        "skill_name" : "仙人指路",
        "damage_type": "瘀傷"
]),
([      "action": "$N左腳前踏半步，雙掌猛然齊出,一招「釜底抽薪」，向$n的$l拍去",
        "force" : 35,
        "dodge" : 26,
        "parry" : 25,
        "lvl"   : 70,
        "skill_name" : "釜底抽薪",
        "damage_type": "瘀傷"
]),
([      "action": "$N雙手翻飛，化作無數掌影，一招「漫天花舞」，直逼$n",
        "force" : 20,
        "dodge" : 28,
        "parry" : 15,
        "lvl"   : 80,
        "skill_name" : "漫天花舞",
        "damage_type": "瘀傷"
]),
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_combine(string combo)
{
        return combo == "taiji-quan" || combo == "paiyun-shou";
}

int valid_learn(object me)
{

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練武當掌法必須空手。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功火候不夠，無法學武當掌法。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的內力太弱，無法練武當掌法。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("wudang-zhang", 1))
                return notify_fail("你的基本掌法火候不足，無法領會更高深的武當掌法。\n");

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
        level = (int) me->query_skill("wudang-zhang", 1);
        for (i = sizeof(action); i > 0; i--)
            if (level > action[i-1]["lvl"])
                return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<100 )
                return notify_fail("你現在手足酸軟，休息一下再練吧。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠了。\n");

        me->receive_damage("qi", 80);
        addn("neili", -50, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"wudang-zhang/" + action;
}