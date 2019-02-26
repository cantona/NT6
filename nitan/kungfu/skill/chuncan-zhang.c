inherit SKILL;

mapping *action = ({
([      "action" : "$N一式「破繭出籠」，雙掌間升起一團淡淡的白霧，緩緩推向$n的$l",
        "force" : 30,
        "dodge" : 15,
        "parry" : 20,
        "damage": 1,
        "lvl" : 0,
        "skill_name" : "破繭出籠",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N使一式「錦綢抽絲」，左掌凝重，右掌輕盈，同時向$n的$l擊去",
        "force" : 55,
        "dodge" : 28,
        "parry" : 25,
        "damage": 3,
        "lvl" : 20,
        "skill_name" : "錦綢抽絲",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N突地一招「蠶絲綿綿」，雙掌挾着一陣風雷之勢，猛地劈往$n的$l",
        "force" : 70,
        "dodge" : 42,
        "parry" : 38,
        "damage": 9,
        "lvl" : 40,
        "skill_name" : "蠶絲綿綿",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N一式「千絲萬縷」，雙掌縵妙地一陣揮舞，不覺已擊到$n的$l上",
        "force" : 91,
        "dodge" : 53,
        "parry" : 49,
        "damage": 12,
        "lvl" : 80,
        "skill_name" : "千絲萬縷",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N一式「碧蠶春生」，身形凝立不動，雙掌一高一低，看似簡單，卻令$n無法躲閃",
        "force" : 102,
        "dodge" : 61,
        "parry" : 57,
        "damage": 18,
        "lvl" : 120,
        "skill_name" : "碧蠶春生",
        "damage_type" : "瘀傷"
])
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_combine(string combo) { return combo == "hujia-quan"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練春蠶掌法必須空手。\n");

        if ((int)me->query_skill("force") < 40)
                return notify_fail("你的內功火候不夠，無法學春蠶掌法。\n");

        if( query("max_neili", me)<300 )
                return notify_fail("你的內力太弱，無法練春蠶掌法。\n");

        if ((int)me->query_skill("strike", 1) < 20)
                return notify_fail("你的基本掌法火候太淺。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("chuncan-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的春蠶掌法。\n");

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
        level = (int) me->query_skill("chuncan-zhang", 1);
        for (i = sizeof(action); i > 0; i--)
            if (level > action[i-1]["lvl"])
                return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠練春蠶掌法。\n");

        me->receive_damage("qi", 45);
        addn("neili", -25, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"chuncan-zhang/" + action;
}