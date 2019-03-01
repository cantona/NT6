#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": "$N端坐不動，一招「縛虎訣」，手中$w抖得筆直，對準$n$l直刺而去",
        "force" : 80,
        "attack": 30,
        "dodge" : 35,
        "parry" : 25,
        "damage": 30,
        "lvl"   : 0,
        "skill_name" : "縛虎訣",
        "damage_type": "刺傷"
]),
([      "action": "$N身形一轉，一招「刺鶴訣」，手中$w如矯龍般騰空一卷，猛地向$n劈頭打下",
        "force" : 130,
        "attack": 38,
        "dodge" : 43,
        "parry" : 27,
        "damage": 45,
        "lvl"   : 40,
        "skill_name" : "刺鶴訣",
        "damage_type": "抽傷"
]),
([      "action": "$N力貫鞭梢，一招「拌馬訣」，手中$w舞出滿天鞭影，舖天蓋地襲向$n全身",
        "force" : 160,
        "attack": 45,
        "dodge" : 63,
        "parry" : 29,
        "damage": 61,
        "lvl"   : 80,
        "skill_name" : "拌馬訣",
        "damage_type": "抽傷"
]),
([      "action":"$N一聲嬌喝，一招「打蛇訣」，手中$w變換莫測，從意想不到的方位掃向$n",
        "force" : 180,
        "attack": 50,
        "dodge" : 65,
        "parry" : 33,
        "damage": 68,
        "lvl"   : 120,
        "skill_name" : "打蛇訣",
        "damage_type": "抽傷"
]),
([      "action":"$N飛身一躍而起，凌空一招「獵豹訣」，$w宛如蛟龍通天，攜著颼颼破空之聲襲向$n",
        "force" : 210,
        "attack": 53,
        "dodge" : 76,
        "parry" : 36,
        "damage": 73,
        "lvl"   : 160,
        "skill_name" : "獵豹訣",
        "damage_type": "抽傷"
]),
([      "action":"$N身形飄逸無定，一招「盤鷹訣」，手中$w幻出無數鞭影，籠罩$n全身",
        "force" : 230,
        "attack": 65,
        "dodge" : 92,
        "parry" : 35,
        "damage": 91,
        "lvl"   : 180,
        "skill_name":  "盤鷹訣",
        "damage_type": "抽傷"
]),
([      "action":"$N身形飄逸無定，一招「擒龍訣」，手中$w幻出無數鞭影，籠罩$n全身",
        "force" : 251,
        "attack": 66,
        "dodge" : 117,
        "parry" : 40,
        "damage": 120,
        "lvl"   : 200,
        "skill_name" : "擒龍訣",
        "damage_type": "抽傷"
]),
});

int valid_enable(string usage) { return usage == "whip" || usage == "parry"; }

int valid_learn(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "whip" )
                return notify_fail("你必須先找一條鞭子才能練劍盾珠索。\n");

        if( query("max_neili", me)<500 )
                return notify_fail("你的內力不足，沒有辦法練劍盾珠索。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候太淺，沒有辦法練劍盾珠索。\n");

        if ((int)me->query_skill("whip", 1) < 20)
                return notify_fail("你的基本鞭法火候太淺，沒有辦法練劍盾珠索。\n");

        if ((int)me->query_skill("whip", 1) < (int)me->query_skill("jiandun-zhusuo", 1))
                return notify_fail("你的基本鞭法水平還不夠，無法領會更高深的劍盾珠索。\n");

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
        level = (int) me->query_skill("jiandun-zhusuo", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠練劍盾珠索。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練劍盾珠索。\n");

        me->receive_damage("qi", 45);
        addn("neili", -55, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"jiandun-zhusuo/" + action;
}