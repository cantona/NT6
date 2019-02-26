inherit SKILL;

mapping *action = ({
([      "action": "$N向前斜跨一步，一招「劍氣封喉」，手中$w直刺$n的喉部",
        "force" : 126,
        "parry" : 3,
        "dodge" : 5,
        "damage": 21,
        "lvl"   : 0,
        "skill_name" : "劍氣封喉",
        "damage_type":  "刺傷"
]),
([      "action": "$N錯步上前，一招「明月千里」，劍意若有若無，$w淡淡地向$n的$l揮去",
        "force" : 149,
        "parry" : 13,
        "dodge" : 10,
        "damage": 25,
        "lvl"   : 30,
        "skill_name" : "明月千里",
        "damage_type":  "割傷"
]),
([      "action": "$N一式「懷中抱月」，縱身飄開數尺，運發劍氣，手中$w遙搖指向$n的$l",
        "force" : 167,
        "parry" : 12,
        "dodge" : 15,
        "damage": 31,
        "lvl"   : 50,
        "skill_name" : "懷中抱月",
        "damage_type":  "刺傷"
]),
([      "action": "$N縱身輕輕躍起，一式「大風起兮」，劍光如水，一瀉千里，灑向$n全身",
        "force" : 187,
        "parry" : 23,
        "dodge" : 19,
        "damage": 45,
        "lvl"   : 70,
        "skill_name" : "大風起兮",
        "damage_type":  "割傷"
]),
([      "action":"$N錯步上前，一招「明月千里」，劍意若有若無，$w淡淡地向$n的$l揮去",
        "force" : 197,
        "parry" : 31,
        "dodge" : 27,
        "damage": 56,
        "lvl"   : 90,
        "skill_name" : "明月千里",
        "damage_type":  "割傷"
]),
([      "action":"$N手中$w中宮直進，一式「定天一針」，無聲無息地對準$n的$l刺出一劍",
        "force" : 218,
        "parry" : 49,
        "dodge" : 35,
        "damage": 63,
        "lvl"   : 110,
        "skill_name" : "定天一針",
        "damage_type":  "刺傷"
]),
([      "action":"$N手中$w一沉，一式「星歸月向」，無聲無息地滑向$n的$l",
        "force" : 239,
        "parry" : 52,
        "dodge" : 45,
        "damage": 72,
        "lvl"   : 130,
        "skill_name" : "星歸月向",
        "damage_type":  "刺傷"
]),
([      "action":"$N手中$w斜指蒼天，劍芒吞吐，一式「映月無聲」，對準$n的$l斜斜擊出",
        "force" : 257,
        "parry" : 55,
        "dodge" : 51,
        "damage": 88,
        "lvl"   : 150,
        "skill_name" : "映月無聲",
        "damage_type":  "刺傷"
]),
([      "action":"$N左指凌空虛點，右手$w逼出丈許雪亮劍芒，一式「情連航慈」刺向$n的咽喉",
        "force" : 282,
        "parry" : 63,
        "dodge" : 55,
        "damage": 105,
        "lvl"   : 170,
        "skill_name" : "情連航慈",
        "damage_type":  "刺傷"
]),
([      "action":"$N合掌跌坐，一式「影玉徵輝」，$w自懷中躍出，如疾電般射向$n的胸口",
        "force" : 331,
        "parry" : 76,
        "dodge" : 65,
        "damage": 122,
        "lvl"   : 190,
        "skill_name" : "影玉徵輝",
        "damage_type":  "刺傷"
])
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if (me->query_skill("force") < 120)
                return notify_fail("你的內功火候不夠，不能學習流月劍舞。\n");

        if (me->query_skill("sword", 1) < 80)
                return notify_fail("你的基本劍法火候不夠，不能學習流月劍舞。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力不夠，不能學習流月劍舞。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("liuyue-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的流月劍舞。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("liuyue-jian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的體力不夠練流月劍舞。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練流月劍舞。\n");

        me->receive_damage("qi", 60);
        addn("neili", -60, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"liuyue-jian/" + action;
}