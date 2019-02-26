inherit SKILL;

mapping *action = ({
([      "action": "$N劍尖劍芒暴長，一招「碧漾劍」，手中$w大開大闔，劍芒直刺$n的$l",
        "force" : 98,
        "attack": 13,
        "dodge" : 2,
        "parry" : 3,
        "damage": 41,
        "lvl"   : 0,
        "skill_name"  : "碧漾劍",
        "damage_type" : "刺傷"
]),
([      "action": "$N劍芒吞吐，單手$w一招「傲寒劍」，劍勢曼妙，劍光直逼向$n的$l",
        "force" : 132,
        "attack": 19,
        "dodge" : 3,
        "parry" : 4,
        "damage": 58,
        "lvl"  : 30,
        "skill_name"  : "傲寒劍",
        "damage_type" : "刺傷"
]),
([      "action": "$N一式「刺骨劍」，屈腕雲劍，劍光如彩碟紛飛，幻出點點星光飄向$n",
        "force" : 163,
        "attack": 23,
        "dodge" : 9,
        "parry" : 10,
        "damage": 77,
        "lvl"   : 60,
        "skill_name"  : "刺骨劍",
        "damage_type" : "刺傷"
]),
([      "action": "$N揮劍分擊，劍勢自胸前躍出，$w一式「驚神劍」，毫無留戀之勢，刺向$n",
        "force" : 190,
        "attack": 31,
        "dodge" : 11,
        "parry" : 13,
        "damage": 85,
        "lvl"   : 100,
        "skill_name"  : "驚神劍",
        "damage_type" : "刺傷"
]),
([      "action": "$N左手劍指劃轉，腰部一扭，右手$w一記「闢塵劍」自下而上刺向$n的$l",
        "force" : 225,
        "attack": 35,
        "dodge" : 5,
        "parry" : 7,
        "damage": 93,
        "lvl"   : 150,
        "skill_name"  : "闢塵劍",
        "damage_type" : "刺傷"
]),
});

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力修為不足。\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("sword", 1) < 80)
                return notify_fail("你的基本劍法火候太淺。\n");

        if (me->query_skill("sword", 1) < me->query_skill("pichen-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的闢塵劍法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;

        level = (int) me->query_skill("pichen-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                       return action[NewRandom(i, 20, level/5)];

}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<60 )
                return notify_fail("你的體力不夠練闢塵劍法。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練闢塵劍法。\n");

        me->receive_damage("qi", 50);
        addn("neili", -55, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"pichen-jian/" + action;
}
