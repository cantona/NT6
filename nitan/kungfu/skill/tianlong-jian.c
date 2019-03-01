inherit SKILL;

mapping *action = ({
([      "action": "$N向前斜跨一步，一招「鯉躍龍門」，手中$w直刺$n的喉部",
        "force" : 126,
        "parry" : 3,
        "dodge" : 5,
        "damage": 21,
        "lvl"   : 0,
        "skill_name" : "鯉躍龍門",
        "damage_type":  "刺傷"
]),
([      "action": "$N錯步上前，一招「神蛟初現」，劍意若有若無，$w淡淡地向$n的$l揮去",
        "force" : 149,
        "parry" : 13,
        "dodge" : 10,
        "damage": 25,
        "lvl"   : 20,
        "skill_name" : "神蛟初現",
        "damage_type":  "割傷"
]),
([      "action": "$N一式「電破長空」，縱身飄開數尺，運發劍氣，手中$w遙搖指向$n的$l",
        "force" : 167,
        "parry" : 12,
        "dodge" : 15,
        "damage": 31,
        "lvl"   : 40,
        "skill_name" : "電破長空",
        "damage_type":  "刺傷"
]),
([      "action": "$N縱身輕輕躍起，一式「天龍探爪」，劍光如水，一瀉千裡，洒向$n全身",
        "force" : 187,
        "parry" : 23,
        "dodge" : 19,
        "damage": 45,
        "lvl"   : 60,
        "skill_name" : "天龍探爪",
        "damage_type":  "割傷"
]),
([      "action":"$N錯步上前，一招「飛龍橫空」，劍意若有若無，$w淡淡地向$n的$l揮去",
        "force" : 197,
        "parry" : 31,
        "dodge" : 27,
        "damage": 56,
        "lvl"   : 90,
        "skill_name" : "飛龍橫空",
        "damage_type":  "割傷"
]),
([      "action":"$N手中$w中宮直進，一式「龍翔鳳舞」，無聲無息地對準$n的$l刺出一劍",
        "force" : 218,
        "parry" : 49,
        "dodge" : 35,
        "damage": 63,
        "lvl"   : 120,
        "skill_name" : "龍翔鳳舞",
        "damage_type":  "刺傷"
]),
([      "action":"$N手中$w一沉，一式「天外遊龍」，劍勢頓時無聲無息地滑向$n$l而去",
        "force" : 239,
        "parry" : 52,
        "dodge" : 45,
        "damage": 72,
        "lvl"   : 150,
        "skill_name" : "天外遊龍",
        "damage_type":  "刺傷"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if (me->query_skill("force") < 70)
                return notify_fail("你的內功火候不夠，不能學習天龍劍法。\n");

        if (me->query_skill("sword", 1) < 40)
                return notify_fail("你的基本劍法火候不夠，不能學習天龍劍法。\n");

        if( query("max_neili", me)<500 )
                return notify_fail("你的內力不夠，不能學習天龍劍法。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("tianlong-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的天龍劍法。\n");

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
        level = (int) me->query_skill("tianlong-jian",1);
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

        if( query("qi", me)<60 )
                return notify_fail("你的體力不夠練天龍劍法。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練天龍劍法。\n");

        me->receive_damage("qi", 52);
        addn("neili", -53, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tianlong-jian/" + action;
}