// longcheng-shendao.c 龍城神刀

inherit SKILL;

mapping *action = ({
([      "action": "$N手中$w輕揮，一招「冬去春來」，身形一轉，一刀向$n的$l撩去",
        "force" : 120,
        "attack": 25,
        "dodge" : 10,
        "parry" : 40,
        "damage": 30,
        "lvl"   : 0,
        "skill_name" : "冬去春來",
        "damage_type" : "割傷"
]),
([      "action": "$N一招「月上西樓」，左腳虛點，$w一收一推，平刃揮向$n的臉部",
        "force" : 160,
        "attack": 28,
        "dodge" : 12,
        "parry" : 45,
        "damage": 45,
        "lvl"   : 30,
        "skill_name" : "月上西樓",
        "damage_type" : "割傷"
]),
([      "action": "$N虛步側身，一招「推窗望月」，刀鋒一卷，攔腰斬向$n",
        "force" : 200,
        "attack": 31,
        "dodge" : 25,
        "parry" : 49,
        "damage": 65,
        "lvl"   : 60,
        "skill_name" : "推窗望月",
        "damage_type" : "割傷"
]),
([      "action": "$N一招「夢斷巫山」，$w自上而下劃出一個大弧，筆直劈向$n",    
        "force" : 240,
        "attack": 48,
        "dodge" : 25,
        "parry" : 54,
        "damage": 80,
        "lvl"   : 90,
        "skill_name" : "夢斷巫山",
        "damage_type" : "割傷"
]),
([      "action": "$N側步擰身，一招「似是而非」，攔腰反切，$w砍向$n的胸口",    
        "force" : 270,
        "attack": 60,
        "dodge" : 30,
        "parry" : 72,
        "damage": 90,
        "lvl"   : 120,
        "skill_name" : "似是而非",
        "damage_type" : "割傷"
]),
([      "action": "$N揮舞$w，使出一招「月掛中天」，幻起片片刀影，齊齊罩向$n",
        "force" : 300,
        "attack": 71,
        "dodge" : 35,
        "parry" : 80,
        "damage": 96,
        "lvl"   : 150,
        "skill_name" : "月掛中天",
        "damage_type" : "割傷"
]),
([      "action": "$N一招「日月交輝」，只見漫天刀光閃爍，重重刀影向$n的全身湧去",
        "force" : 330,
        "attack": 80,
        "dodge" : 42,
        "parry" : 94,
        "damage": 105,
        "lvl"   : 180,
        "skill_name" : "日月交輝",
        "damage_type" : "割傷"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; } 

int valid_learn(object me)
{
        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("blade", 1) < 80)
                return notify_fail("你的基本刀法火候不夠。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("longcheng-shendao", 1))
                return notify_fail("你的刀法水平有限，無法領會更高深的龍城神刀。\n");

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
        level = (int) me->query_skill("longcheng-shendao",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力不夠練龍城神刀。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練龍城神刀。\n");

        me->receive_damage("qi", 65);
        addn("neili", -68, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"longcheng-shendao/" + action;
}