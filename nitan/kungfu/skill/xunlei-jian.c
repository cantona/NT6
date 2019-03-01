inherit SKILL;

mapping *action = ({
([        "action": "$N劍尖向右，繞身一周，一式「仙人指路」，$w突然向$n的$l刺去，",
        "force" : 35,
        "dodge" : -40,
        "parry" : -40,
        "attack": 2,
        "damage": 3,
        "lvl"   : 0,
        "skill_name" : "仙人指路",
        "damage_type":"刺傷"
]),
([        "action": "$N使出一式「鷂子翻身」，身體凌空側翻，一劍從身下刺出",
        "force" : 49,
        "dodge" : -35,
        "parry" : -35,
        "attack": 3,
        "damage": 4,
        "lvl"   : 10,
        "skill_name" : "鷂子翻身",
        "damage_type":"刺傷"
]),
([        "action": "$N左手劍指血指，右手$w使出一招「海底尋針」，由上至下猛向$n的$l劈刺",
        "force" : 57,
        "dodge" : -23,
        "parry" : -23,
        "attack": 5,
        "damage": 7,
        "lvl"   : 20,
        "skill_name" : "海底尋針",
        "damage_type":"刺傷"
]),
([        "action": "$N撤步縮身，$w按藏于臂下，一招「靈猿探洞」，快如閃電般刺向$n的$l",
        "force" : 63,
        "dodge" : -18,
        "parry" : -18,
        "attack": 9,
        "damage": 10,
        "lvl"   : 30,
        "skill_name" : "靈猿探洞",
        "damage_type":"刺傷"
]),
([        "action": "$N踏步向前，一式「撥草尋蛇」，手中長劍擺動，劍尖刺向$n的$l",
        "force" : 67,
        "dodge" : -9,
        "parry" : -9,
        "attack": 11,
        "damage": 12,
        "lvl"   : 40,
        "skill_name" : "撥草尋蛇",
        "damage_type":"刺傷"
]),
([        "action": "$N一招「斜插神枝」，身體背轉，手中$w由右肩上方反手向下刺出",
        "force" : 79,
        "dodge" : -5,
        "parry" : -5,
        "attack": 13,
        "damage": 14,
        "lvl"   : 50,
        "skill_name" : "斜插神枝",
        "damage_type":"劈傷"
]),
([        "action": "$N一式「電閃雷動」，劍走中鋒，氣勢威嚴，將$n籠罩于重重劍氣之中",
        "force" : 87,
        "dodge" : 5,
        "parry" : 5,
        "attack": 15,
        "damage": 16,
        "lvl"   : 60,
        "skill_name" : "電閃雷動",
        "damage_type":"劈傷"
]),
([        "action": "$N向前彎身，一招「夫子揖手」，$w忽然從身下刺出，快如流星閃電",
        "force" : 90,
        "dodge" : 10,
        "parry" : 10,
        "attack": 18,
        "damage": 20,
        "lvl"   : 70,
        "skill_name" : "夫子揖手",
        "damage_type":"刺傷"
]),
([        "action": "$N橫握$w，左右晃動，一招「玉帶纏腰」，劍氣直逼$n的腰部要害",
        "force" : 105,
        "dodge" : 14,
        "parry" : 14,
        "attack": 20,
        "damage": 24,
        "lvl"   : 80,
        "skill_name" : "玉帶纏腰",
        "damage_type":"刺傷"
]),
([        "action": "$N雙手持劍，將$w當做刀使，一招「舉火燒天」，由身後向$n的前上方劈去",
        "force" : 110,
        "dodge" : 18,
        "parry" : 18,
        "attack": 24,
        "damage": 28,
        "lvl"   : 90,
        "skill_name" : "舉火燒天",
        "damage_type":"刺傷"
]),
([        "action": "$N側身向$n，使出一招「敗馬斬蹄」，揮動手中$w，直劈$n的下三路",
        "force" : 120,
        "dodge" : 20,
        "parry" : 20,
        "attack": 26,
        "damage": 30,
        "lvl"   : 100,
        "skill_name" : "敗馬斬蹄",
        "damage_type":"刺傷"
]),
([        "action": "$N手中$w由右自左，一招「玉女穿針」，$w突然反手刺向$n的$l",
        "force" : 135,
        "dodge" : 24,
        "parry" : 24,
        "attack": 30,
        "damage": 35,
        "lvl"   : 110,
        "skill_name" : "玉女穿針",
        "damage_type":"刺傷"
]),
([        "action": "$N跳步向前，劍尖上指，一招「靈猿登枝」，$w挑向$n的頭部要害",
        "force" : 140,
        "dodge" : 26,
        "parry" : 26,
        "attack": 31,
        "damage": 36,
        "lvl"   : 120,
        "skill_name" : "靈猿登枝",
        "damage_type":"刺傷"
]),
([        "action": "$N一招「蘇武揮鞭」，$w隨身走，猶如一條白龍，將$n全身上下籠罩",
        "force" : 145,
        "dodge" : 28,
        "parry" : 28,
        "attack": 33,
        "damage": 38,
        "lvl"   : 130,
        "skill_name" : "蘇武揮鞭",
        "damage_type":"刺傷"
]),
([        "action": "$N劍尖向下，一招「挑燈看劍」，$w忽然急轉直上，劍氣將$n的上身要害團團圍住",
        "force" : 150,
        "dodge" : 30,
        "parry" : 30,
        "attack": 35,
        "damage": 40,
        "lvl"   : 140,
        "skill_name" : "挑燈看劍",
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

        if ((int)me->query_skill("sword") < 10)
                return notify_fail("你的基本劍法火候太淺，無法修煉迅雷劍法。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("xunlei-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的迅雷劍法。\n");

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
        level = (int) me->query_skill("xunlei-jian", 1);
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
                return notify_fail("你的體力不夠練迅雷劍法。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠練迅雷劍法。\n");

        me->receive_damage("qi", 50);
        addn("neili", -45, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"xunlei-jian/" + action;
}