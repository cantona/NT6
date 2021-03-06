inherit SKILL;

mapping *action = ({
([      "action" : "$N站立如鬆，一式「刀山戮骨」，兩股拳風破氣而發，擊向$n的$l",
        "force"  : 40,
        "attack" : 8,
        "parry"  : 3,
        "dodge"  : 2,
        "damage" : 5,
        "lvl"    : 0,
        "skill_name"  : "刀山戮骨",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N一式「火海焚心」，左拳下擊，右拳隨後直衝，勢如地裂",
        "force"  : 55,
        "attack" : 9,
        "parry"  : 1,
        "dodge"  : 2,
        "damage" : 7,
        "lvl"    : 10,
            "skill_name"  : "火海焚心",
            "damage_type" : "瘀傷"
]),
([          "action" : "$N騰空飛起，一式「歸天」，拳式變腿招踢出，$n急忙躲閃",    
        "force"  : 64,
        "attack" : 12,
        "parry"  : 5,
        "dodge"  : 3,
        "damage" : 9,
        "lvl"    : 30,
            "skill_name"  : "歸天",
            "damage_type" : "瘀傷"
]),
([          "action" : "$N雙拳劃開，疾風突起，一式「鎮魂」，向$n發出",
        "force"  : 71,
        "attack" : 13,
        "parry"  : 4,
        "dodge"  : 6,
        "damage" : 11,
        "lvl"    : 50,
            "skill_name"  : "鎮魂",
            "damage_type" : "瘀傷"
]),
([          "action" : "$N兩臂後展，拳招變掌，一式「煉獄」，插向$n的掖下死穴",    
        "force"  : 84,
        "attack" : 18,
        "parry"  : 13,
        "dodge"  : 12,
        "damage" : 15,
        "lvl"    : 70,
            "skill_name"  : "煉獄",
            "damage_type" : "瘀傷"
]),
([          "action" : "$N跨前一步，施一式「修羅索命」，拳變指，點向$n的胸前死穴",
        "force"  : 93,
        "attack" : 21,
        "parry"  : 7,
        "dodge"  : 9,
        "damage" : 19,
        "lvl"    : 90,
            "skill_name"  : "修羅索命",
            "damage_type" : "瘀傷"
]),
([          "action" : "$N出其不意，從上而下，一式「魂飛魄散」，四周空氣先凝集後突爆開",
        "force"  : 101,
        "attack" : 24,
        "parry"  : 8,
        "dodge"  : 12,
        "damage" : 25,
        "lvl"    : 120,
            "skill_name"  : "魂飛魄散",
           "damage_type" : "瘀傷"
]),
([          "action" : "$N眼眉一皺，雙拳破氣齊發，一式「孤山鬼嚎」，擊向$n的頭額",
        "force"  : 140,
        "attack" : 28,
        "parry"  : 13,
        "dodge"  : 12,
        "damage" : 27,
        "lvl"    : 150,
            "skill_name"  : "孤山鬼嚎",
            "damage_type" : "瘀傷"
])
});

int valid_enable(string usage)
{
        return usage == "cuff" || usage == "parry";
}

int valid_combine(string combo)
{
        return combo == "poyue-zhao";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練鎮獄拳法必須空手。\n");

        if ((int)me->query_skill("force") < 20)
                return notify_fail("你的內功火候不夠，無法學鎮獄拳法。\n");

        if( query("max_neili", me)<200 )
                return notify_fail("你的內力修為太淺，無法練鎮獄拳法。\n");

        if ((int)me->query_skill("cuff", 1) < 10)
                return notify_fail("你的基本拳法火候太淺，無法練鎮獄拳法。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("zhenyu-quan", 1))
                return notify_fail("你的基本拳法水平有限，無法領會更高深的鎮獄拳法。\n");

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
        level = (int) me->query_skill("zhenyu-quan", 1);
        for (i = sizeof(action); i > 0; i--)
            if (level > action[i-1]["lvl"])
                return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠練鎮獄拳法。\n");

        me->receive_damage("qi", 45);
        addn("neili", -25, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"zhenyu-quan/" + action;
}