inherit SKILL;

mapping *action = ({
([      "action" : "$N一式「攀陽手」，左手帶風，右手拍向$n的$l",
        "force"  : 30,
        "attack" : 5,
        "dodge"  : 15,
        "parry"  : 20,
        "damage" : 10,
        "lvl"    : 0,        
        "damage_type" : "瘀傷",
        "skill_name"  : "攀陽手"
]),
([      "action" : "$N右手微台，直出向前，一式「拂月掌」，疾向$n的$l擊去",
        "force"  : 45,
        "attack" : 8,
        "dodge"  : 20,
        "parry"  : 35,
        "damage" : 13,
        "lvl"    : 10,      
        "damage_type" : "瘀傷",
        "skill_name"  : "拂月掌"
]),
([      "action" : "$N使一式「逆風式」，左掌微拂，右掌順勢而進，猛地插往$n的$l",
        "force"  : 60,
        "attack" : 12,
        "dodge"  : 25,
        "parry"  : 20,
        "damage" : 15,
        "lvl"    : 25,        
        "damage_type" : "瘀傷",
        "skill_name"  : "逆風式"
]),
([      "action" : "$N雙掌隱隱泛出青氣，一式「風雲手」，掌風激勁，雨點般向$n擊去",
        "force"  : 76,
        "attack" : 15,
        "dodge"  : 30,
        "parry"  : 25,
        "damage" : 18,
        "lvl"    : 38,      
        "damage_type" : "瘀傷",
        "skill_name"  : "風雲手"
]),
([      "action" : "$N雙掌不斷反轉，使出一式「折手式」，雙掌並攏，筆直地向$n的$l襲去",
        "force"  : 52,
        "attack" : 18,
        "dodge"  : 33,
        "parry"  : 30,
        "damage" : 25,
        "lvl"    : 55,       
        "damage_type" : "瘀傷",
        "skill_name"  : "折手式"
]),
([      "action" : "$N身形一變，使一式「齊掌式」，雙掌帶著蕭剎的勁氣，猛地擊往$n的$l",
        "force"  : 90,
        "attack" : 20,
        "dodge"  : 38,
        "parry"  : 35,
        "damage" : 30,
        "lvl"    : 65,       
        "damage_type" : "瘀傷",
        "skill_name"  : "齊掌式"
]),
([      "action" : "$N使一式「紫煙手」，雙掌如夢似幻，同時向$n的$l擊去",
        "force"  : 120,
        "attack" : 22,
        "dodge"  : 42,
        "parry"  : 38,
        "damage" : 33,
        "lvl"    : 72,        
        "damage_type" : "瘀傷",
        "skill_name"  : "紫煙手"
]),
([      "action" : "$N一式「流水式」，身法忽變，似流雲飄忽，不覺已擊到$n的$l上",
        "force"  : 140,
        "attack" : 24,
        "dodge"  : 45,
        "parry"  : 45,
        "damage" : 38,
        "lvl"    : 80,        
        "damage_type" : "瘀傷",
        "skill_name"  : "流水式"
]),
([      "action" : "$N突地一招「天雷手」，雙掌挾著一陣風雷之勢，猛地劈往$n的$l",
        "force"  : 160,
        "attack" : 26,
        "dodge"  : 50,
        "parry"  : 50,
        "damage" : 50,
        "lvl"    : 90,      
        "damage_type" : "瘀傷",
        "skill_name"  : "天雷手"
]),
});

int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練嵩陽掌必須空手。\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的內功火候不夠，無法學嵩陽掌。\n");

        if( query("max_neili", me)<400 )
                return notify_fail("你的內力太弱，無法嵩陽掌。\n");

        if ((int)me->query_skill("strike", 1) < 80)
                return notify_fail("你的基本掌法火候太淺。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("songyang-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的嵩陽掌。\n");

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
        level = (int) me->query_skill("songyang-zhang", 1);
        for (i = sizeof(action); i > 0; i--)
            if (level > action[i-1]["lvl"])
                return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練嵩陽掌。\n");

        me->receive_damage("qi", 50);
        addn("neili", -45, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"songyang-zhang/" + action;
}