inherit SKILL;

mapping *action = ({
([      "action": "$N使一式「峭壁斷雲」，手中$w疾揮而下，幻出一道孤光刺向$n的$l",
        "force" : 90,
        "attack": 30,
        "dodge" : 10,
        "parry" : 25,
        "damage": 25,
        "lvl"   : 0,
        "skill_name" : "峭壁斷雲",
        "damage_type": "刺傷"
]),
([      "action": "$N錯步上前，一招「無聲無色」，劍意若有若無，$w淡淡刺向$n的$l",
        "force" : 140,
        "attack": 60,
        "dodge" : 25,
        "parry" : 25,
        "damage": 40,
        "lvl"   : 40,
        "skill_name" : "無聲無色",
        "damage_type": "刺傷"
]),
([      "action": "$N一式「西域秋色」，縱身飄開數尺，又猛地錯步上前，手中$w疾刺$n的$l",
        "force" : 180,
        "attack": 60,
        "dodge" : 25,
        "parry" : 28,
        "damage": 40,
        "lvl"   : 80,
        "skill_name" : "西域秋色",
        "damage_type": "刺傷"
]),
([      "action": "$N縱身輕輕躍起，一式「雪融昆侖」，劍光如雨點般的洒向$n",
        "force" : 220,
        "attack": 75,
        "dodge" : 20,
        "parry" : 35,
        "damage": 60,
        "lvl"   : 120,
        "skill_name" : "雪融昆侖",
        "damage_type": "刺傷"
]),
([      "action": "$N手中$w劍芒吞吐，揮洒而出，一式「大漠駝鈴」，對準$n的$l直直刺出",
        "force" : 260,
        "attack": 90,
        "dodge" : 25,
        "parry" : 50,
        "damage": 70,
        "lvl"   : 160,
        "skill_name" : "大漠駝鈴",
        "damage_type": "刺傷"
]),
([      "action": "$N大喝一聲，$w逼出丈許劍芒刺向$n，正是一式「群山疊影」，欲求與$n同亡",
        "force" : 285,
        "attack": 97,
        "dodge" : 31,
        "parry" : 48,
        "damage": 73,
        "lvl"   : 200,
        "skill_name" : "群山疊影",
        "damage_type": "刺傷"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力修為不夠，無法學習昆侖劍法。\n");

        if ((int)me->query_skill("force", 1) < 60)
                return notify_fail("你的內功火候太淺，無法學習昆侖劍法。\n");

        if ((int)me->query_skill("sword", 1) < 60)
                return notify_fail("你的基本劍法火候太淺，無法學習昆侖劍法。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("kunlun-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的昆侖劍法。\n");

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
        level = (int) me->query_skill("kunlun-jian", 1);
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

        if( query("qi", me)<120 )
                return notify_fail("你的體力不夠練昆侖劍法。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練昆侖劍法。\n");

        me->receive_damage("qi", 100);
        addn("neili", -55, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"kunlun-jian/" + action;
}