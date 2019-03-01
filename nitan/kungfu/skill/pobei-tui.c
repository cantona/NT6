inherit SKILL;

mapping *action = ({
([      "action" : "$N雙手虛晃，左腳猛地飛起，一式「開山腿」，踢向$n的$l",
        "force" : 80,
        "attack": 10,
        "dodge" : 15,
        "parry" : 15,
        "damage": 10,
        "lvl"   : 0,
        "damage_type" : "瘀傷",
        "skill_name"  : "開山腿"
]),
([      "action" : "$N左腳頓地，身形猛轉，右腳一式「劈碑腿」，猛踹$n的$l",
        "force" : 100,
        "attack": 20,
        "dodge" : 20,
        "parry" : 20,
        "damage": 15,
        "lvl"   : 30,
        "damage_type" : "瘀傷",
        "skill_name"  : "劈碑腿"
]),
([      "action" : "$N右腳飛一般踹出，既猛且準，一式「碎石腿」，踢向的$n",
        "force" : 140,
        "attack": 30,
        "dodge" : 25,
        "parry" : 25,
        "damage": 18,
        "lvl"   : 60,
        "damage_type" : "瘀傷",
        "skill_name"  : "碎石腿"
]),
([      "action" : "$N雙足連環圈轉，一式「裂地腿」，足帶風塵，攻向$n的全身",
        "force" : 160,
        "attack": 35,
        "dodge" : 30,
        "parry" : 30,
        "damage": 20,
        "lvl"   : 90,
        "damage_type" : "瘀傷",
        "skill_name"  : "裂地腿"
]),
([      "action" : "$N雙腳交叉踢起，一式「鑽天腿」，腳腳不離$n的面門左右",
        "force" : 180,
        "attack": 35,
        "dodge" : 40,
        "parry" : 40,
        "damage": 25,
        "lvl"   : 120,
        "damage_type" : "瘀傷",
        "skill_name"  : "鑽天腿"
]),
});

int valid_enable(string usage) { return usage=="unarmed" ||  usage=="parry"; } 

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練破碑腿必須空手。\n");

        if ((int)me->query_skill("force") < 40)
                return notify_fail("你的內功火候不夠，無法學破碑腿。\n");

        if ((int)me->query_skill("unarmed", 1) < 20)
                return notify_fail("你的基本拳腳火候不夠，無法學破碑腿。\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("pobei-tui", 1))
                return notify_fail("你的基本拳腳水平有限，無法領會更高深的破碑腿。\n");

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
        level = (int)me->query_skill("pobei-tui", 1);
        for(i = sizeof(action); i > 0; i--)
            if(level > action[i-1]["lvl"])
                return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<100 )
               return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<80 )
               return notify_fail("你的內力不夠練破碑腿。\n");

        me->receive_damage("qi", 80);
        addn("neili", -60, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"pobei-tui/" + action;
}