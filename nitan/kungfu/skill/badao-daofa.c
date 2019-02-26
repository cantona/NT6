inherit SKILL;

mapping *action = ({
([      "action" : "$N藏刀內收，刀鋒自下而上劃了個半弧，向$n的$l揮去",
        "force" : 193,
        "dodge" : 3,
        "parry" : 5,
        "damage": 61,
        "attack": 33,
        "lvl" : 0,
        "damage_type" : "割傷"
]),
([      "action" : "$N左掌虛託右肘，手中$w筆直划向$n的$l",
        "force" : 217,
        "dodge" : 9,
        "parry" : 7,
        "damage": 68,
        "attack": 37,
        "lvl" : 20,
        "damage_type" : "割傷"
]),
([      "action" : "$N手中$w繞頸而過，刷地一聲自上而下向$n猛劈",
        "force" : 225,
        "dodge" : 13,
        "parry" : 7,
        "damage": 73,
        "attack": 38,
        "lvl" : 40,
        "damage_type" : "割傷"
]),
([      "action" : "$N右手反執刀柄，猛一挫身，$w直向$n的頸中斬去",
        "force" : 239,
        "dodge" : 11,
        "parry" : 9,
        "damage": 79,
        "attack": 41,
        "lvl" : 60,
        "damage_type" : "割傷"
]),
([      "action" : "$N手中$w幻出無數刀尖，化作點點繁星，向$n的$l挑去",
        "force" : 257,
        "dodge" : 11,
        "parry" : 13,
        "damage": 83,
        "attack": 48,
        "lvl" : 80,
        "damage_type" : "割傷"
]),
([      "action" : "$N雙手合執$w，擰身急轉，刀尖直刺向$n的雙眼",
        "force" : 276,
        "dodge" : 19,
        "parry" : 23,
        "damage": 89,
        "attack": 53,
        "lvl" : 100,
        "damage_type" : "割傷"
]),
([      "action" : "$N手中$w劃出一個大平十字，向$n縱橫劈去",
        "force" : 312,
        "dodge" : 17,
        "parry" : 13,
        "damage": 97,
        "attack": 59,
        "lvl" : 120,
        "damage_type" : "割傷"
]),
([      "action" : "$N反轉刀尖對準自己，全身一個翻滾，$w向$n攔腰斬去",
        "force" : 297,
        "dodge" : 18,
        "parry" : 21,
        "damage": 113,
        "attack": 68,
        "lvl" : 140,
        "damage_type" : "割傷"
]),
([      "action" : "$N手中$w的刀光彷彿化成一簇簇烈焰，將$n團團圍繞",
        "force" : 323,
        "dodge" : 29,
        "parry" : 23,
        "damage": 117,
        "attack": 69,
        "lvl" : 170,
        "damage_type" : "割傷"
]),
([      "action" : "$N刀尖平指，一片片切骨刀氣如颶風般裹向$n的全身",
        "force" : 317,
        "dodge" : 31,
        "parry" : 25,
        "damage": 121,
        "attack": 78,
        "lvl" : 200,
        "damage_type" : "割傷"
]),
});

int valid_enable(string usage) { return (usage == "blade") || (usage == "parry")
; }

int valid_learn(object me)
{
        if( query("character", me) != "心狠手辣" )
                return notify_fail("你覺得這霸刀刀法實在過於狠毒，自己委實學不會。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力不足，沒有辦法練霸刀刀法，多練些內力再來吧。\n");

        if ((int)me->query_skill("blade", 1) < 180)
                return notify_fail("你的基本刀法火候太淺，沒有辦法練霸刀刀法。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候太淺，沒有辦法練霸刀刀法。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("badao-daofa", 1))
                return notify_fail("你的基本刀法水平還不夠，無法領會更高深的霸刀刀法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("badao-daofa",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的體力不夠練霸刀刀法。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練霸刀刀法。\n");

        me->receive_damage("qi", 60);
        addn("neili", -60, me);
        return 1;
}
