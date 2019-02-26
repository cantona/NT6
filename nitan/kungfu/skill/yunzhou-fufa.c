#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": "$N右手微抬，一招「長空萬里」，手中$w筆直刺向$n",
        "force" : 45,
        "dodge" : 35,
        "parry" : 12,
        "damage": 15,
        "lvl"   : 0,
        "damage_type": "刺傷"
]),
([      "action": "$N身形一轉，手中$w如矯龍般騰空一卷，猛地向$n劈頭打下",
        "force" : 80,
        "dodge" : 28,
        "parry" : 15,
        "damage": 30,
        "lvl"   : 30,
        "damage_type": "抽傷"
]),
([      "action": "$N一聲長嘯，手中$w揮舞得呼呼作響，如長龍般地襲向$n全身",
        "force" : 116,
        "dodge" : 43,
        "parry" : 29,
        "damage": 51,
        "lvl"   : 50,
        "damage_type": "抽傷"
]),
([      "action":"$N身法忽變，忽左忽右，手中$w龍吟不定只向$n$l",
        "force" : 180,
        "dodge" : 55,
        "parry" : 33,
        "damage": 60,
        "lvl"   : 80,
        "damage_type": "抽傷"
]),
([      "action":"$N飛身一躍而起，$w宛如游龍，破空而下，攻向$n",
        "force" : 210,
        "dodge" : 65,
        "parry" : 36,
        "damage": 80,
        "lvl"   : 110,
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
                return notify_fail("你必須先找一條鞭子才能練雲帚拂法。\n");

        if( query("max_neili", me)<400 )
                return notify_fail("你的內力不足，沒有辦法練雲帚拂法，多練些內力再來吧。\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的內功火候太淺，沒有辦法練雲帚拂法。\n");

        if ((int)me->query_skill("whip", 1) < 20)
                return notify_fail("你的基本鞭法火候太淺，沒有辦法練雲帚拂法。\n");

        if ((int)me->query_skill("whip", 1) < (int)me->query_skill("yunzhou-fufa", 1))
                return notify_fail("你的基本鞭法水平還不夠，無法領會更高深的雲帚拂法。\n");

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
        level = (int) me->query_skill("yunzhou-fufa", 1);
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

        if( query("qi", me)<40 )
                return notify_fail("你的體力不夠練雲帚拂法。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠練雲帚拂法。\n");

        me->receive_damage("qi", 35);
        addn("neili", -40, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yunzhou-fufa/" + action;
}