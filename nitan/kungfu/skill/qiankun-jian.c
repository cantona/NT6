inherit SKILL;

mapping *action = ({
([      "action": "$N手中的$w盪出，一招「太陽劍」，就如大江東去，勢不可擋",
        "force" : 153,
        "attack": 39,
        "dodge" : 65,
        "parry" : 67,
        "damage": 41,
        "lvl"   : 0,
        "skill_name" : "太陽劍",
        "damage_type": "割傷"
]),
([      "action": "$N踏上一步，一招「少陰劍」，手中$w舞出一道劍光劈向$n的$l",
        "force" : 167,
        "attack": 43,
        "dodge" : 68,
        "parry" : 69,
        "damage": 43,
        "lvl"   : 20,
        "skill_name" : "少陰劍",
        "damage_type": "割傷"
]),
([      "action": "$N手中$w一抖，一招「少陽劍」，一劍刺向$n的$l，沒有半點花巧",
        "force" : 173,
        "attack": 48,
        "dodge" : 71,
        "parry" : 79,
        "damage": 45,
        "lvl"   : 40,
        "skill_name" : "少陽劍",
        "damage_type": "割傷"
]),
([      "action": "$N手中$w微微顫動，一招「太陰劍」，忽然刺出，頓時一道劍光射向$n的$l",
        "force" : 195,
        "attack": 51,
        "dodge" : 75,
        "parry" : 82,
        "damage": 49,
        "lvl"   : 60,
        "skill_name" : "太陰劍",
        "damage_type": "刺傷"
]),
([      "action": "$N身形一轉，一招「天地定位」，橫過$w，驀然橫掃$n，氣勢如宏",
        "force" : 218,
        "attack": 57,
        "dodge" : 79,
        "parry" : 83,
        "damage": 53,
        "lvl"   : 80,
        "skill_name" : "天地定位",
        "damage_type": "割傷"
]),
([      "action": "$N手中的$w連削帶刺，一招「山澤通氣」，夾帶著一陣旋風掠過$n全身",
        "force" : 224,
        "attack": 62,
        "dodge" : 85,
        "parry" : 89,
        "damage": 57,
        "lvl"   : 100,
        "skill_name" : "山澤通氣",
        "damage_type": "刺傷"
]),
([      "action": "$N身形一轉，一招「雷風相薄」，手中$w猛然攻下，驀然橫掃$n，氣勢如宏",
        "force" : 238,
        "attack": 69,
        "dodge" : 87,
        "parry" : 91,
        "damage": 61,
        "lvl"   : 130,
        "skill_name" : "雷風相薄",
        "damage_type": "割傷"
]),
([      "action": "$N手中的$w連削帶刺，一招「水火不射」，夾帶著一陣旋風掠過$n全身",
        "force" : 257,
        "attack": 75,
        "dodge" : 95,
        "parry" : 99,
        "damage": 68,
        "lvl"   : 160,
        "skill_name" : "水火不射",
        "damage_type": "刺傷"
]),
([      "action": "$N身形一轉，一招「八卦相錯」，橫轉$w驀然橫掃$n，氣勢如宏",
        "force" : 270,
        "attack": 81,
        "dodge" : 107,
        "parry" : 109,
        "damage": 73,
        "lvl"   : 190,
        "skill_name" : "八卦相錯",
        "damage_type": "割傷"
]),
([      "action": "$N手中的$w連削帶刺，一招「乾坤無極」，夾帶著一陣旋風掠過$n全身",
        "force" : 285,
        "attack": 85,
        "dodge" : 115,
        "parry" : 115,
        "damage": 77,
        "lvl"   : 220,
        "skill_name" : "乾坤無極",
        "damage_type": "刺傷"
])
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 180)
                return notify_fail("你的內功火候不到，無法學習乾坤神劍。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力太差，無法學習乾坤神劍。\n");

        if ((int)me->query_skill("sword", 1) < 150)
                return notify_fail("你的基本劍法火候太淺，無法學習乾坤神劍。\n");

        if (me->query_skill("sword", 1) < me->query_skill("qiankun-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的乾坤神劍。\n");

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
        level = (int) me->query_skill("qiankun-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的體力不夠練乾坤神劍。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練乾坤神劍。\n");

        me->receive_damage("qi", 65);
        addn("neili", -70, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"qiankun-jian/" + action;
}