inherit SKILL;

mapping *action = ({
([      "action":"$N使一式「星辰滿天」，手中$w由左至右橫掃向向$n的$l",
        "force" : 70,
        "attack": 10,
        "dodge" : 10,
        "damage": 13,
        "lvl" : 0,
        "skill_name" : "星辰滿天",
        "damage_type":  "割傷"
]),
([      "action":"$N踏上一步，「七星聚月」，手中$w盤旋飛舞出一道劍光劈向$n的$l",
        "force" : 74,
        "attack": 15,
        "dodge" : 20,
        "damage": 19,
        "lvl" : 10,
        "skill_name" : "七星聚月",
        "damage_type":  "割傷"
]),
([      "action":"$N手中$w一抖，一招「偏花七星」，斜斜一劍反腕撩出，攻向$n的$l",
        "force" : 85,
        "attack": 20,
        "dodge" : 25,
        "damage": 21,
        "lvl" : 20,
        "skill_name" : "偏花七星",
        "damage_type":  "割傷"
]),
([      "action":"$N手中$w連繞數個大圈，一式「星弛電閃」，一道劍光飛向$n的$l",
        "force" : 118,
        "attack": 25,
        "dodge" : 30,
        "damage": 28,
        "lvl" : 30,
        "skill_name" : "星弛電閃",
        "damage_type":  "刺傷"
]),
([      "action":"$N一式「橫移北鬥」，左手伸展，右手$w揮向$n的$l",
        "force" : 130,
        "attack": 30,
        "dodge" : 35,
        "damage": 32,
        "lvl" : 40,
        "skill_name" : "橫移北鬥",
        "damage_type":  "割傷"
]),
([      "action":"$N手中$w斜指蒼天，一式「七星匯聚」，對準$n的$l斜斜擊出",
        "force" : 150,
        "attack": 33,
        "dodge" : 45,
        "damage": 39,
        "lvl" : 50,
        "skill_name" : "七星匯聚",
        "damage_type":  "刺傷"
]),
([      "action":"$N一式「朝拜天罡」，$w飛斬盤旋，如疾電般射向$n的胸口",
        "force" : 193,
        "attack": 40,
        "dodge" : 55,
        "damage": 54,
        "lvl" : 60,
        "skill_name" : "朝拜天罡",
        "damage_type":  "刺傷"
]),
([      "action":"$N使一式「劍轉七星」，手中$w合身疾刺$n的胸口，威不可當",
        "force" : 220,
        "attack": 45,
        "dodge" : 55,
        "damage": 63,
        "lvl" : 80,
        "skill_name" : "劍轉七星",
        "damage_type":  "刺傷"
])
});

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力修為太差，無法學習七星劍法。\n");

        if (me->query_skill("sword", 1) < 10)
                return notify_fail("你的基本劍法修為不夠，無法學習七星劍法。\n");

        if (me->query_skill("sword", 1) < me->query_skill("qixing-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的七星劍法。\n");

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
        level = (int) me->query_skill("qixing-jian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<40 )
                return notify_fail("你的體力不夠練七星劍法。\n");

        if( query("neili", me)<40 )
                return notify_fail("你的內力不夠練七星劍法。\n");

        me->receive_damage("qi", 35);
        addn("neili", -33, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"qixing-jian/" + action;
}