// SKILL liuyang-zhang.c

inherit SKILL;

mapping *action = ({
([        "action" : "$N一招「無對」，左掌疊於右掌之上，劈向$n",
        "force" : 130,
        "dodge" : 20,
        "damage" : 10,
        "lvl" : 0,
        "skill_name" : "無對",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N一招「無雙」，面色詭異，雙掌輕飄飄地拍向$n",
        "force" : 150,
        "dodge" : 10,
        "damage" : 30,
        "lvl" : 20,
        "skill_name" : "無雙",
        "damage_type" : "內傷"
]),
([        "action" : "$N一招「無拘」，雙掌幻化一片幻影，將$n籠罩於內。",
        "force" : 150,
        "dodge" : 30,
        "damage" : 35,
        "lvl" : 30,
        "skill_name" : "無拘",
        "damage_type" : "瘀傷"
]),

([        "action" : "$N一招「無束」，向$n的$l連擊三掌",
        "force" : 200,
        "dodge" : 25,
        "damage" : 50,
        "lvl" : 40,
        "skill_name" : "無束",
    "damage_type" : "瘀傷"
]),
([        "action" : "$N一招「無聲」，只見一片掌影攻向$n",
        "force" : 250,
        "dodge" : 20,
        "damage" : 70,
        "lvl" : 40,
        "skill_name" : "無聲",
        "damage_type" : "瘀傷"
]),

([        "action" : "$N雙掌平揮，不見掌影,不聞掌風,一招「無息」擊向$n",
        "force" : 300,
        "dodge" : 25,
        "damage" : 80,
        "lvl" : 60,
        "skill_name" : "無息",
            "damage_type" : "瘀傷"
]),
([        "action" : "$N一招「無影」，只見一片紅影罩向$n",
        "force" : 350,
        "dodge" : 30,
        "damage" : 90,
        "lvl" : 70,
        "skill_name" : "無影",
        "damage_type" : "內傷"
]),

([        "action" : "$N左掌虛晃，右掌一記「無蹤」擊向$n的頭部",
        "force" : 350,
        "dodge" : 50,
        "damage" : 120,
        "lvl" : 80,
        "skill_name" : "無蹤",
           "damage_type" : "瘀傷"
]),

});

int valid_enable(string usage) { return usage=="unarmed" || usage=="parry"; }
int valid_combine(string combo) { return combo=="dashou-yin"; }


int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練無影神拳必須空手。\n");
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力太弱，無法練無影神拳。\n");

        return 1;
}

//mapping query_action(object me, object weapon)
//{
//        int i, level;
//        level = (int) me->query_skill("wuying-shenquan",1);
//        for(i = sizeof(action); i > 0; i--)
//                if(level > action[i-1]["lvl"])
//                        return action[NewRandom(i, 20, level/5)];
//}
/* ----------------
mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}
-------------------*/


mapping query_action(object me, object weapon)
{
        int i, level;
    level   = (int) me->query_skill("wuying-shenquan",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 5, level/5)];

}

int practice_skill(object me)
{
        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練無影神拳。\n");
        me->receive_damage("qi", 25);
        addn("neili", -10, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"wuying-shenquan/" + action;
}