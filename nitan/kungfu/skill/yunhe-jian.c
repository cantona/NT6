inherit SKILL;

mapping *action = ({
([        "action": "$N劍尖向右，繞身一週，一式「百鶴鳴曉」，$w突然向$n的$l刺去，",
        "force" : 35,
        "dodge" : -40,
        "parry" : -40,
        "attack": 2,
        "damage": 3,
        "lvl"   : 0,
        "skill_name" : "百鶴鳴曉",
        "damage_type":"刺傷"
]),
([        "action": "$N使出一式「仙鶴西來」，身體凌空側翻，一劍從身下刺出",
        "force" : 59,
        "dodge" : -35,
        "parry" : -35,
        "attack": 3,
        "damage": 4,
        "lvl"   : 20,
        "skill_name" : "仙鶴西來",
        "damage_type":"刺傷"
]),
([        "action": "$N左手劍指血指，右手$w使出一招「乘鶴東歸」，由上至下猛向$n的$l劈刺",
        "force" : 77,
        "dodge" : -23,
        "parry" : -23,
        "attack": 5,
        "damage": 7,
        "lvl"   : 40,
        "skill_name" : "乘鶴東歸",
        "damage_type":"刺傷"
]),
([        "action": "$N撤步縮身，$w按藏於臂下，一招「一鶴衝宵」，快如閃電般刺向$n的$l",
        "force" : 83,
        "dodge" : -18,
        "parry" : -18,
        "attack": 9,
        "damage": 10,
        "lvl"   : 60,
        "skill_name" : "一鶴衝宵",
        "damage_type":"刺傷"
]),
([        "action": "$N踏步向前，一式「鶴貝相爭」，手中長劍擺動，劍尖刺向$n的$l",
        "force" : 127,
        "dodge" : -9,
        "parry" : -9,
        "attack": 11,
        "damage": 12,
        "lvl"   : 80,
        "skill_name" : "鶴貝相爭",
        "damage_type":"刺傷"
]),
([        "action": "$N一招「雲鶴三舞」，身體背轉，手中$w由右肩上方反手向下刺出",
        "force" : 179,
        "dodge" : -5,
        "parry" : -5,
        "attack": 31,
        "damage": 44,
        "lvl"   : 100,
        "skill_name" : "雲鶴三舞",
        "damage_type":"劈傷"
]),
([        "action": "$N一式「雲鶴七舞」，劍走中鋒，氣勢威嚴，將$n籠罩於重重劍氣之中",
        "force" : 217,
        "dodge" : 5,
        "parry" : 5,
        "attack": 35,
        "damage": 56,
        "lvl"   : 130,
        "skill_name" : "雲鶴七舞",
        "damage_type":"劈傷"
]),
([        "action": "$N向前彎身，一招「雲鶴九舞」，$w忽然從身下刺出，快如流星閃電",
        "force" : 260,
        "dodge" : 10,
        "parry" : 10,
        "attack": 48,
        "damage": 72,
        "lvl"   : 160,
        "skill_name" : "雲鶴九舞",
        "damage_type":"刺傷"
]),
([        "action": "$N橫握$w，左右晃動，一招「鶴舞十二天」，劍氣直逼$n的腰部要害",
        "force" : 305,
        "dodge" : 14,
        "parry" : 14,
        "attack": 51,
        "damage": 84,
        "lvl"   : 200,
        "skill_name" : "鶴舞十二天",
        "damage_type":"刺傷"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 20)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("sword") < 30)
                return notify_fail("你的基本劍法火候太淺，無法修煉雲鶴七劍。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("yunhe-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的雲鶴七劍。\n");

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
        level = (int) me->query_skill("yunhe-jian", 1);
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

        if( query("qi", me)<60 )
                return notify_fail("你的體力不夠練雲鶴七劍。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠練雲鶴七劍。\n");

        me->receive_damage("qi", 50);
        addn("neili", -45, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yunhe-jian/" + action;
}