#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N端坐不動，一招「破元勢」，手中$w抖得筆直，對準$n的胸腹要害連刺數鞭",
        "force" : 180,
        "attack": 20,
        "dodge" : 2,
        "parry" : 1,
        "damage": 49,
        "lvl"   : 0,
        "skill_name" : "破元勢",
        "damage_type": "刺傷"
]),
([      "action": "$N身形一轉，一招「吞金勢」，手中$w如矯龍般騰空一卷，猛地向$n劈頭打下",
        "force" : 200,
        "attack": 28,
        "dodge" : 3,
        "parry" : 5,
        "damage": 61,
        "lvl"   : 30,
        "skill_name" : "吞金勢",
        "damage_type": "抽傷"
]),
([      "action": "$N力貫鞭梢，一招「盪妖勢」，手中$w舞出滿天鞭影，排山倒海般掃向$n全身",
        "force" : 210,
        "attack": 35,
        "dodge" : 2,
        "parry" : 5,
        "damage": 73,
        "lvl"   : 60,
        "skill_name" : "盪妖勢",
        "damage_type": "抽傷"
]),
([      "action":"$N力貫鞭梢，一招「伏魔勢」，手中$w舞出滿天鞭影，排山倒海般掃向$n全身",
        "force" : 220,
        "attack": 41,
        "dodge" : 5,
        "parry" : 6,
        "damage": 84,
        "lvl"   : 90,
        "skill_name" : "伏魔勢",
        "damage_type": "抽傷"
]),
([      "action":"$N力貫鞭梢，一招「寰穹勢」，手中$w舞出滿天鞭影，排山倒海般掃向$n全身",
        "force" : 230,
        "attack": 47,
        "dodge" : 6,
        "parry" : 15,
        "damage": 95,
        "lvl"   : 120,
        "skill_name" : "寰穹勢",
        "damage_type": "抽傷"
]),
([      "action":"$N力貫鞭梢，一招「戮神勢」，手中$w舞出滿天鞭影，排山倒海般掃向$n全身",
        "force" : 240,
        "attack": 55,
        "dodge" : 12,
        "parry" : 20,
        "damage": 110,
        "lvl"   : 150,
        "skill_name":  "戮神勢",
        "damage_type": "抽傷"
]),
([      "action":"$N力貫鞭梢，一招「雷轟勢」，手中$w舞出滿天鞭影，排山倒海般掃向$n全身",
        "force" : 260,
        "attack": 61,
        "dodge" : 17,
        "parry" : 25,
        "damage": 130,
        "lvl"   : 180,
        "skill_name" : "雷轟勢",
        "damage_type": "抽傷"
]),
([      "action":"$N力貫鞭梢，一招「盤龍勢」，手中$w舞出滿天鞭影，排山倒海般掃向$n全身",
        "force" : 290,
        "attack": 68,
        "dodge" : 20,
        "parry" : 35,
        "damage": 149,
        "lvl"   : 220,
        "skill_name" : "盤龍勢",
        "damage_type": "抽傷"
]),
});

int valid_enable(string usage)
{
        return usage == "whip" || usage == "parry";
}

int valid_learn(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "whip" )
                return notify_fail("你必須先找一條鞭子才能練鞭法。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的內力修為不足，無法修煉霹靂盤龍索。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候太淺，無法修煉霹靂盤龍索。\n");

        if ((int)me->query_skill("whip", 1) < 80)
                return notify_fail("你的基本鞭法火候太淺，無法修煉霹靂盤龍索。\n");

        if ((int)me->query_skill("whip", 1) < (int)me->query_skill("panlong-suo", 1))
                return notify_fail("你的基本鞭法水平還不夠，無法領會更高深的霹靂盤龍索。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("panlong-suo",1);
        for(i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的體力不夠練霹靂盤龍索。\n");

        if( query("neili", me)<90 )
                return notify_fail("你的內力不夠練霹靂盤龍索。\n");

        me->receive_damage("qi", 75);
        addn("neili", -85, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"panlong-suo/" + action;
}