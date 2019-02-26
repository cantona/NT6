inherit SKILL;

mapping *action = ({
([        "action" : "$N一招「斜陽照路」，左掌疊於右掌之上，劈向$n",
        "force" : 80,
        "attack": 2,
        "dodge" : 30,
        "parry" : 1,
        "damage": 5,
        "lvl"   : 0,
        "skill_name" : "斜陽照路",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N一招「千山鳥飛絕」，面色凝重，雙掌輕飄飄地拍向$n",
        "force" : 100,
        "attack": 8,
        "dodge" : 25,
        "parry" : 3,
        "damage": 30,
        "lvl"   : 20,
        "skill_name" : "千山鳥飛絕",
        "damage_type" : "內傷"
]),
([        "action" : "$N一招「長空明淨」，雙掌幻化一片掌影，將$n籠罩於內。",
        "force" : 130,
        "attack": 12,
        "dodge" : 43,
        "parry" : 4,
        "damage": 35,
        "lvl"   : 30,
        "skill_name" : "長空明淨",
        "damage_type" : "瘀傷"
]),

([        "action" : "$N一招「萬水千山」，向$n的$l連擊數掌",
        "force" : 150,
        "attack": 15,
        "dodge" : 55,
        "parry" : 8,
        "damage": 50,
        "lvl"   : 40,
        "skill_name" : "萬水千山",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N一招「萬徑人蹤滅」，只見一片掌影攻向$n",
        "force" : 180,
        "attack": 22,
        "dodge" : 52,
        "parry" : 0,
        "damage": 30,
        "lvl"   : 60,
        "skill_name" : "萬徑人蹤滅",
        "damage_type" : "瘀傷"
]),

([        "action" : "$N雙掌平揮，一招「過關斬將」擊向$n",
        "force" : 230,
        "attack": 23,
        "dodge" : 65,
        "parry" : 11,
        "damage": 50,
        "lvl"   : 80,
        "skill_name" : "過關斬將",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N一招「彩雲遮月」，只見一片掌影攻向$n",
        "force" : 260,
        "attack": 28,
        "dodge" : 63,
        "parry" : 5,
        "damage": 80,
        "lvl"   : 100,
        "skill_name" : "彩雲遮月",
        "damage_type" : "內傷"
]),

([        "action" : "$N施出「高山流水」，右手橫掃$n的$l，左手攻向$n的胸口",
        "force" : 280,
        "attack": 25,
        "dodge" : 77,
        "damage": 90,
        "parry" : 12,
        "lvl"   : 120,
        "skill_name" : "高山流水",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N左掌虛晃，右掌一記「夕陽西下」擊向$n的頭部",
        "force" : 320,
        "attack": 31,
        "dodge" : 80,
        "parry" : 15,
        "damage": 100,
        "lvl"   : 140,
        "skill_name" : "夕陽西下",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N施出「萬毒噬體」，雙掌同時擊向$n的$l",
        "force" : 360,
        "attack": 32,
        "dodge" : 81,
        "parry" : 10,
        "damage": 130,
        "lvl"   : 160,
        "skill_name" : "萬毒噬體",
        "damage_type" : "瘀傷"
])
});

int valid_enable(string usage)
{
        return usage == "parry" || usage == "strike";
}

int valid_learn(object me)
{
        if( query("character", me) != "心狠手辣" && query("character", me) != "國士無雙" )
                return notify_fail("練五毒神掌必須要心狠手辣，我看你這點做得還不夠。\n"); 

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練五毒神掌必須空手。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，無法練五毒神掌。\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("你的內力太弱，無法練五毒神掌。\n");

        if ((int)me->query_skill("strike", 1) < 120)
                return notify_fail("你的基本掌法火候不夠，無法練五毒神掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("wudu-shenzhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的五毒神掌。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("wudu-shenzhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<90 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練五毒神掌。\n");

        me->receive_damage("qi", 81);
        addn("neili", -73, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"wudu-shenzhang/" + action;
}