// ruanhong-zhusuo.c 軟紅蛛索
// by Vin 2000

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": "$N端坐不動，一式「天蛛盤絲」，手腕力抬，$w滾動飛舞，宛如靈蛇亂顫掃向$n",
        "force" : 98,
        "attack": 41,
        "dodge" : -5,
        "parry" : 15,
        "damage": 32,
        "lvl"   : 0,
        "damage_type": "抽傷"
]),
([      "action": "$N一式「蛛絲馬跡」，$w抖得筆直，“呲呲”破空聲中向$n疾刺而去",
        "force" : 187,
        "attack": 48,
        "dodge" : -20,
        "parry" : 36,
        "damage": 47,
        "lvl"   : 80,
        "damage_type": "刺傷"
]),
([      "action": "$N內勁到處，將$w抖動轉成兩個圓圈，一式「靈蛛奪食」，從半空中往$n纏下",
        "force" : 231,
        "attack": 65,
        "dodge" : -10,
        "parry" : 55,
        "damage": 93,
        "lvl"   : 100,
        "damage_type": "抽傷"
]),
([        "action": "$N勁走螺旋，一式「蛛網織天」，$w在$n眼前連變數種招式，忽然從$l處倒卷上來",
        "force" : 263,
        "attack": 70,
        "dodge" : 5,
        "parry" : 60,
        "damage": 102,
        "lvl"   : 120,
        "damage_type": "抽傷"
]),
([        "action": "$N一聲高喝，使出「龍蛛捉蟒」，$w急速轉動，鞭影縱橫，似真似幻，絞向$n",
        "force" : 301,
        "attack": 77,
        "dodge" : 6,
        "parry" : 65,
        "damage": 121,
        "lvl"   : 140,
        "damage_type": "抽傷"
]),
([        "action": "$N含胸拔背，一式「金蛛銀索」，力道靈動威猛，勁力從四面八方向$n擠壓出去",
        "force" : 331,
        "attack": 85,
        "dodge" : 12,
        "parry" : 70,
        "damage": 142,
        "lvl"   : 160,
        "damage_type": "抽傷"
]),
([        "action":"$N力貫鞭梢，一招「天虹密布」，手中$w舞出滿天鞭影，排山倒海般掃向$n全身",
        "force" : 373,
        "attack": 91,
        "dodge" : 17,
        "parry" : 75,
        "damage": 163,
        "lvl"   : 180,
        "damage_type": "抽傷"
]),
([        "action":"$N力貫鞭梢，一招「天地蠶食」，手中$w舞出滿天鞭影，排山倒海般掃向$n全身",
        "force" : 401,
        "attack": 98,
        "dodge" : 20,
        "parry" : 85,
        "damage": 189,
        "lvl"   : 200,
        "damage_type": "抽傷"
]),
});

int valid_enable(string usage) { return usage == "whip" || usage == "parry"; }

int valid_learn(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "whip" )
                return notify_fail("你必須先找一條鞭子才能練軟紅蛛索。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力不足，沒有辦法練軟紅蛛索，多練些內力再來吧。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候太淺，沒有辦法練軟紅蛛索。\n");

        if ((int)me->query_skill("whip", 1) < 100)
                return notify_fail("你的基本鞭法火候太淺，沒有辦法練軟紅蛛索。\n");

        if ((int)me->query_skill("whip", 1) < (int)me->query_skill("ruanhong-zhusuo", 1))
                return notify_fail("你的基本鞭法水平還不夠，無法領會更高深的軟紅蛛索。\n");

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
        level = (int) me->query_skill("ruanhong-zhusuo",1);
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
                return notify_fail("你的體力不夠練軟紅蛛索。\n");

        if( query("neili", me)<90 )
                return notify_fail("你的內力不夠練軟紅蛛索。\n");

        me->receive_damage("qi", 75);
        addn("neili", -85, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"ruanhong-zhusuo/" + action;
}