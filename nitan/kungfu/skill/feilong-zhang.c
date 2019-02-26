inherit SKILL;

mapping *action = ({
([      "action": "$N斜舉$w, 一招「秦王鞭石」，斜肩鏟背砸向$n的$l",
        "force" : 80,
        "attack": 24,
        "dodge" : -5,
        "parry" : 20,
        "damage": 35,
        "lvl"   : 0,
        "damage_type":"挫傷"
]),
([      "action": "$N一聲大喝，使出一招「魯達拔柳」, 手中$w自下而上掃向$n的$l",
        "force" : 100,
        "attack": 30,
        "dodge" : -10,
        "parry" : 25,
        "damage": 40,
        "lvl"   : 30,
        "damage_type":"挫傷"
]),
([      "action": "$N使出一招「霸王扛鼎」，將$w從肩頭甩出砸嚮往$n的$l",
        "force" : 120,
        "attack": 35,
        "dodge" : -5,
        "parry" : 24,
        "damage": 50,
        "lvl"   : 70,
        "damage_type":"挫傷"
]),
([      "action": "$N身子一晃，一招「八仙醉打」，手中$w如狂風暴雨般向$n打出",
        "force" : 160,
        "attack": 50,
        "dodge" : -5,
        "parry" : 45,
        "damage": 60,
        "lvl"   : 100,
        "damage_type":"挫傷"
]),
([      "action": "$N一聲咆哮，一招「長虹經天」, $w從手中擲出，飛向$n的$l",
        "force" : 180,
        "attack": 61,
        "dodge" : -5,
        "parry" : 50,
        "damage": 75,
        "lvl"   : 120,
        "damage_type":"挫傷"
]),
([      "action": "$N一招「飛龍一現」, 將手中$w舞成千百根相似，根根砸向$n全身各處要害",
        "force" : 220,
        "attack": 70,
        "dodge" : -5,
        "parry" : 60,
        "damage": 90,
        "lvl"   : 150, 
        "damage_type":"挫傷"
]),
});

int valid_enable(string usage)
{
        return usage == "staff" || usage == "parry";
}

int valid_learn(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不對。\n");

        if( query("max_neili", me)<500 )
                return notify_fail("你的內力修為不足，難以修煉飛龍杖法。\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的內功修為不夠，難以修煉飛龍杖法。\n");

        if ((int)me->query_skill("staff", 1) < 40)
                return notify_fail("你的基本杖法火候太淺，難以修煉飛龍杖法。\n");

        if ((int)me->query_skill("staff", 1) < (int)(int)me->query_skill("feilong-zhang", 1))
                return notify_fail("你的基本杖法水平有限，無法領會更高深的飛龍杖法。\n");

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
        level = (int) me->query_skill("feilong-zhang", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的體力不夠練飛龍杖法。\n");

        if( query("neili", me)<75 )
                return notify_fail("你的內力不夠練飛龍杖法。\n");

        me->receive_damage("qi", 70);
        addn("neili", -69, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"feilong-zhang/" + action;
}
