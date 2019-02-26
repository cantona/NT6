inherit SKILL;

mapping *action = ({
([      "skill_name": "陽關三疊",
        "action": "$N雙掌一錯，一招「陽關三疊」幻出層層掌影奔向$n的$l",
        "force" : 70,
        "attack": 5,
        "dodge" : 20,
        "parry" : 20,
        "damage": 50,
        "lvl"   : 0,
        "damage_type":  "瘀傷"
]),
([      "skill_name": "地久天長",
        "action": "$N暴喝一聲，單掌猛然推出，一招「地久天長」強勁的掌風直撲$n的$l",
        "force" : 90,
        "attack": 10,
        "dodge" : 25,
        "parry" : 25,
        "damage": 50,
        "lvl"   : 15,
        "damage_type":  "瘀傷"
]),
([      "skill_name": "金龍戲水",
        "action": "$N雙掌紛飛，一招「金龍戲水」直取$n的$l",
        "force" : 110,
        "attack": 20,
        "dodge" : 32,
        "parry" : 32,
        "damage": 33,
        "lvl"   : 30,
        "damage_type": "瘀傷"
]),
([      "skill_name": "萬物復甦",
        "action": "$N按北斗方位急走，一招「萬物復甦」，陣陣掌風無孔不入般地擊向$n的$l",
        "force" : 140,
        "attack": 30,
        "dodge" : 30,
        "parry" : 45,
        "damage": 70,
        "lvl"   : 50,
        "damage_type": "瘀傷"
]),
([      "skill_name": "回光反照",
        "action": "$N回身錯步，雙掌平推，凝神聚氣，一招「回光反照」拍向$n的$l",
        "force" : 170,
        "attack": 35,
        "dodge" : 45,
        "parry" : 50,
        "damage": 30,
        "lvl"   : 70,
        "damage_type": "瘀傷"
]),
([      "skill_name": "神光乍現",
        "action": "$N左掌立於胸前，右掌推出，一招「神光乍現」迅然擊向$n$l",
        "force" : 190,
        "attack": 40,
        "dodge" : 50,
        "parry" : 52,
        "damage": 30,
        "lvl"   : 90,
        "damage_type": "瘀傷"
]),
([      "skill_name": "百里千長",
        "action": "$N使出「百里千長」，身形急進，快速向$n出掌攻擊",
        "force" : 220,
        "attack": 40,
        "dodge" : 65,
        "parry" : 55,
        "damage": 30,
        "lvl"   : 110,
        "damage_type": "瘀傷"
]),
([      "skill_name": "星遊九天",
        "action": "$N一招「星遊九天」，雙掌虛虛實實的擊向$n的$l",
        "force" : 250,
        "attack": 45,
        "dodge" : 60,
        "parry" : 57,
        "damage": 30,
        "lvl"   : 130,
        "damage_type": "瘀傷"
]),
([      "skill_name": "北斗易位",
        "action": "$N左掌畫了個圈圈，右掌推出，一招「北斗易位」擊向$n$l",
        "force" : 270,
        "attack": 50,
        "dodge" : 68,
        "parry" : 61,
        "damage": 30,
        "lvl"   : 150,
        "damage_type": "瘀傷"
]),
});

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練重陽神掌必須空手。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的內力修為不足，無法練重陽神掌。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，無法練重陽神掌。\n");

        if ((int)me->query_skill("strike", 1) < 100)
                return notify_fail("你的基本掌法水平有限，無法學重陽神掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("chongyang-shenzhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的重陽神掌。\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_combine(string combo)
{
        return combo == "zhongnan-zhi";
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("chongyang-shenzhang", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("你的體力不夠了，休息一下再練吧。\n");

        if( query("neili", me)<65 )
                return notify_fail("你的內力不夠了，休息一下再練吧。\n");

        me->receive_damage("qi", 60);
        addn("force", -55, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"chongyang-shenzhang/" + action;
}