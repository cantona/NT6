// edit by gladiator

inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "$N手中$w斜指，一招「展鞭訣」，反身一頓，一鞭向$n的$l撩去",
        "force" : 20,
        "dodge" : 10,
        "parry" : 25,
        "damage": 5,
        "lvl"   : 0,
        "skill_name"  : "展鞭訣",
        "damage_type" : "割傷"
]),
([      "action": "$N一招「抹鞭訣」，左右腿虛點，$w一提一收，平刃揮向$n的頸部",
        "force" : 30,
        "dodge" : 30,
        "parry" : 40,
        "damage": 10,
        "lvl"   : 20,
        "skill_name"  : "抹鞭訣",
        "damage_type" : "割傷"
]),
([      "action": "$N展身虛步，提腰躍落，一招「剁鞭訣」，鞭鋒一卷，攔腰斬向$n",
        "force" : 40,
        "dodge" : 35,
        "parry" : 45,
        "damage": 15,
        "lvl"   : 40,
        "skill_name"  : "剁鞭訣",
        "damage_type" : "割傷"
]),
([      "action": "$N一招「鉤鞭訣」，$w大開大闔，自上而下劃出一個大弧，筆直劈向$n",
        "force" : 60,
        "dodge" : 45,
        "parry" : 45,
        "damage": 20,
        "lvl"   : 60,
        "skill_name"  : "鉤鞭訣",
        "damage_type" : "割傷"
]),
([      "action": "$N手中$w一沉，一招「砍鞭訣」，雙手持刃攔腰反切，砍向$n的胸口",
        "force" : 80,
        "dodge" : 50,
        "parry" : 55,
        "damage": 25,
        "lvl"   : 80,
        "skill_name"  : "砍鞭訣",
        "damage_type" : "割傷"
]),
([      "action": "$N揮舞$w，使出一招「劈鞭訣」，上劈下撩，左擋右開，齊齊罩向$n",
        "force" : 90,
        "dodge" : 65,
        "parry" : 55,
        "damage": 30,
        "lvl"   : 100,
        "skill_name"  : "劈鞭訣",
        "damage_type" : "割傷"
]),
([      "action": "$N一招「六合總訣」，左腳躍步落地，$w順勢往前，挾風聲劈向$n的$l",
        "force" : 120,
        "dodge" : 75,
        "parry" : 85,
        "damage": 35,
        "lvl"   : 120,
        "skill_name"  : "六合總訣",
        "damage_type" : "割傷"
]),
([      "action": "$N盤身駐地，一招「六勢合一」，揮出一片流光般的鞭影，向$n的全身湧去",
        "force" : 140,
        "dodge" : 90,
        "parry" : 90,
        "damage": 40,
        "lvl"   : 140,
        "skill_name"  : "六勢合一",
        "damage_type" : "割傷"
]),
});


int valid_enable(string usage)
{
        return usage == "whip" || usage == "parry";
}

int valid_learn(object me)
{

        if( query("con", me)<24 )
                  return notify_fail("你的先天根骨暗弱無法修煉六合鞭。\n");
        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力修為不夠。\n");

     if ((int)me->query_skill("force") < 180)
                return notify_fail("你的內功火候太淺。\n");

       if ((int)me->query_skill("whip", 1) < 150)
               return notify_fail("你的基本鞭法火候太淺。\n");

        if ((int)me->query_skill("whip", 1) < (int)me->query_skill("liuhe-bian", 1))
                return notify_fail("你的基本鞭法水平有限，無法領會更高深的六合鞭法。\n");

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
        level = (int) me->query_skill("liuhe-bian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<60 )
                return notify_fail("你的體力不夠練六合鞭法。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練六合鞭法。\n");

        me->receive_damage("qi", 45);
        addn("neili", -43, me);
        return 1;
}

string perform_action_file(string action)
{
             return __DIR__"liuhe-bian/" + action;
}