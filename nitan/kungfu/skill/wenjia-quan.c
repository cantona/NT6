
// wenjia-quan 温家拳 (npc 功夫)

inherit SKILL;

mapping *action = ({
([     "action" : "$N一式「兔戲蒼鷹」，側身揮拳，帶着呼呼的風聲打向$n的$l",
       "force" : 180,
        "dodge" : 20,
        "parry" : -10,
       "lvl" : 0,       
       "damage_type" : "內傷"
]),
([     "action" : "$N左拳虛握，右拳快如閃電般打向$n的$l，正是一招「飛流直瀉」",
       "force" : 205,
        "dodge" : 0,
       "lvl" : 0,
        "damage_type" : "瘀傷"
]),
([     "action" : "$N使招「風雨歸人」，雙拳交錯，忽又分開，引內勁打向$n的$l",
       "force" : 340,
        "dodge" : -10,
        "parry" : 5,
       "lvl" : 10,
        "damage_type" : "內傷"
]),
([     "action" : "$N雙拳猶如狂風驟雨般打向$n，拳影閃爍，已將$n團團圍住",
       "force" : 380,
        "dodge" : 5,
        "parry" : 0,
       "lvl" : 10,
        "damage_type" : "瘀傷"
]),
([     "action" : "$N縱身越起直落在$n身後，雙腳落地後雙拳向後揮出，打向$n的後心。",
       "force" : 390,
        "dodge" : 10,
        "parry" : -5,
       "lvl" : 30,
        "damage_type" : "瘀傷"
]),
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }

int valid_learn(object me)
{
       if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
               return notify_fail("温家拳拳必須空手。\n");
      
       if ((int)me->query("max_neili") < 100)
               return notify_fail("你的內力太弱，無法練功。\n");
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
       level   = (int) me->query_skill("wenjia-quan",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
       if ((int)me->query("jingli") < 30)
               return notify_fail("你的體力太低了。\n");
       if ((int)me->query("neili") < 20)
               return notify_fail("你的內力不夠練温家拳。\n");
       me->receive_damage("jingli", 30);
       me->add("neili", -10);
       return 1;
}


