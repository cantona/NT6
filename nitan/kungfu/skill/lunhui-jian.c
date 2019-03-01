inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "$N使一式「人間道」，手中$w嗡嗡微振，幻成一條疾光刺向$n的$l",
        "force" : 190,
        "attack": 130,
        "dodge" : 110,
        "parry" : 115,
        "damage": 115,
        "lvl"   : 0,
        "skill_name" : "人間道",
        "damage_type": "刺傷"
]),
([      "action": "$N錯步上前，使出「畜生道」，劍意若有若無，$w淡淡地向$n的$l揮去",
        "force" : 240,
        "attack": 150,
        "dodge" : 115,
        "parry" : 125,
        "damage": 130,
        "lvl"   : 40,
        "skill_name" : "畜生道",
        "damage_type": "割傷"
]),
([      "action": "$N一式「餓鬼道」，縱身飄開數尺，運發劍氣，手中$w遙搖指向$n的$l",
        "force" : 260,
        "attack": 160,
        "dodge" : 125,
        "parry" : 128,
        "damage": 140,
        "lvl"   : 80,
        "skill_name" : "餓鬼道",
        "damage_type": "割傷"
]),
([      "action": "$N縱身輕輕躍起，一式「修羅道」，劍光如輪疾轉，霍霍斬向$n的$l",
        "force" : 280,
        "attack": 170,
        "dodge" : 120,
        "parry" : 135,
        "damage": 155,
        "lvl"   : 120,
        "skill_name" : "修羅道",
        "damage_type": "割傷"
]),
([      "action": "$N手中$w中宮直進，一式「地獄道」，無聲無息地對準$n的$l刺出一劍",
        "force" : 320,
        "attack": 180,
        "dodge" : 125,
        "parry" : 142,
        "damage": 160,
        "lvl"   : 160,
        "skill_name" : "地獄道",
        "damage_type": "刺傷"
]),
([      "action": "$N手中$w斜指蒼天，劍芒吞吐，一式「天極道」，對準$n的$l斜斜擊出",
        "force" : 360,
        "attack": 185,
        "dodge" : 125,
        "parry" : 151,
        "damage": 170,
        "lvl"   : 200,
        "skill_name" : "天極道",
        "damage_type": "刺傷"
]),
([      "action": "$N左指凌空虛點，右手$w逼出丈許雪亮劍芒，一式「六道輪回」翻轉向$n",
        "force" : 390,
        "attack": 190,
        "dodge" : 130,
        "parry" : 159,
        "damage": 175,
        "lvl"   : 240,
        "skill_name" : "六道輪回",
        "damage_type": "刺傷"
]),
});

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
        if( query("max_neili", me)<5000 )
                return notify_fail("你的內力修為不夠，難以修煉釋迦輪回劍。\n");

        if ((int)me->query_skill("force") < 350)
                return notify_fail("你的內功火候太淺，難以修煉釋迦輪回劍。\n");

        if ((int)me->query_skill("sword", 1) < 250)
                return notify_fail("你的劍法根基不足，難以修煉釋迦輪回劍。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("lunhui-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的釋迦輪回劍。\n");

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
        level = (int) me->query_skill("lunhui-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<120 )
                return notify_fail("你的體力不夠練釋迦輪回劍。\n");

        if( query("neili", me)<150 )
                return notify_fail("你的內力不夠練釋迦輪回劍。\n");

        me->receive_damage("qi", 100);
        addn("neili", -120, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"lunhui-jian/" + action;
}