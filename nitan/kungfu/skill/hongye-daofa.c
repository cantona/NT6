// hongye-daofa.c 紅葉刀法

inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action" : "$N手中$w輕揮，一招「冬去春來」，身形一轉，一刀向$n的$l撩去",
        "force" : 100,
        "attack" : 10,
        "dodge" : -10,
        "parry" : -1,
        "damage" : 30,
        "lvl" : 0,
        "skill_name" : "冬去春來",
        "damage_type" : "割傷"
]),
([      "action" : "$N一招「月上西樓」，左腳虛點，$w一收一推，平刃揮向$n的臉部",
    "force" : 130,
    "attack" : 40,
    "dodge" : -10,
    "parry" : 5,
    "damage" : 58,
    "lvl" : 20,
    "skill_name" : "月上西樓",
    "damage_type" : "割傷"
]),
([      "action" : "$N虛步側身，一招「推窗望月」，刀鋒一卷，攔腰斬向$n",
    "force" : 160,
    "attack" : 40,
    "parry" : 25,
    "dodge" : -5,
    "damage" : 80,
    "lvl" : 40,
    "skill_name" : "推窗望月",
    "damage_type" : "割傷"
]),
([      "action" : "$N一招「夢斷巫山」，$w自上而下劃出一個大弧，筆直劈向$n",    
    "force" : 190,
    "attack" : 55,
    "dodge" : 5,
    "parry" : 35,
    "damage" : 105,
    "lvl" : 60,
    "skill_name" : "夢斷巫山",
    "damage_type" : "割傷"
]),
([      "action" : "$N側步擰身，一招「似是而非」，攔腰反切，$w砍向$n的胸口",    
    "force" : 220,
    "attack" : 60,
    "dodge" : 10,
    "parry" : 40,
    "damage" : 95,
    "lvl" : 80,
    "skill_name" : "似是而非",
    "damage_type" : "割傷"
]),
([      "action" : "$N揮舞$w，使出一招「紅葉紛紛」，幻起片片刀影，齊齊罩向$n",  
    "force" : 240,
    "attack" : 70,
    "dodge" : 15,
    "parry" : 55,
    "damage" : 140,
    "lvl" : 100,
    "skill_name" : "月掛中天",
    "damage_type" : "割傷"
]),
([      "action" : "$N一招「日月交輝」，只見漫天刀光閃爍，重重刀影向$n的全身湧去
",
    "force" : 320,
    "attack" : 70,
    "dodge" : 20,
    "parry" : 60,
    "damage" : 160,
    "damage" : 130,
    "lvl" : 120,
    "skill_name" : "日月交輝",
    "damage_type" : "割傷"
]),
});


int valid_enable(string usage) { return usage == "blade" || usage == "parry"; } 

int valid_learn(object me)
{
    if( query("max_neili", me)<2000 )
   return notify_fail("你的內力不夠。\n");
    if (me->query_skill("force", 1) < 150)
   return notify_fail("你的內功火候太淺。\n");
    if (me->query_skill("blade", 1) < 150)
   return notify_fail("你的基本刀法火候太淺。\n");
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
    level   = (int) me->query_skill("hongye-daofa",1);
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
    if( query("qi", me)<50 )
   return notify_fail("你的體力不夠練紅葉刀法。\n");
    if( query("neili", me)<80 )
   return notify_fail("你的內力不夠練紅葉刀法。\n");
    me->receive_damage("qi", 25);
    addn("neili", -35, me);
    return 1;
}

string perform_action_file(string action)
{
    return __DIR__"hongye-daofa/" + action;
}
