inherit SKILL;

mapping *action = ({
([      "action": "$N手中$w斜指，一招「□蛇翻身」，反身一頓，一刀向$n的$l撩去",
        "force" : 20,
        "dodge" : 10,
        "parry" : 25,
        "damage": 5,
        "lvl"   : 0,
        "skill_name"  : "□蛇翻身",
        "damage_type" : "割傷"
]),
([      "action": "$N一招「巨蟒纏身」，左右腿虛點，$w一提一收，平刃揮向$n的頸部",
        "force" : 30,
        "dodge" : 30,
        "parry" : 10,
        "damage": 10,
        "lvl"   : 20,
        "skill_name"  : "巨蟒纏身",
        "damage_type" : "割傷"
]),
([      "action": "$N展身虛步，提腰躍落，一招「蛇蛻于野」，刀鋒一卷，攔腰斬向$n",
        "force" : 40,
        "dodge" : 35,
        "parry" : 25,
        "damage": 11,
        "lvl"   : 40,
        "skill_name"  : "蛇蛻于野",
        "damage_type" : "割傷"
]),
([      "action": "$N一招「曲蛇吐信」，$w大開大闔，自上而下劃出一個大弧，筆直劈向$n",
        "force" : 60,
        "dodge" : 36,
        "parry" : 25,
        "damage": 17,
        "lvl"   : 60,
        "skill_name"  : "曲蛇吐信",
        "damage_type" : "割傷"
]),
([      "action": "$N手中$w一沉，一招「蛇鶴相爭」，雙手持刃攔腰反切，砍向$n的胸口",
        "force" : 80,
        "dodge" : 34,
        "parry" : 35,
        "damage": 21,
        "lvl"   : 80,
        "skill_name"  : "蛇鶴相爭",
        "damage_type" : "割傷"
]),
([      "action": "$N揮舞$w，使出一招「□蟒暴伸」，上劈下撩，左擋右開，齊齊罩向$n",
        "force" : 90,
        "dodge" : 41,
        "parry" : 38,
        "damage": 27,
        "lvl"   : 100,
        "skill_name"  : "□蟒暴伸",
        "damage_type" : "割傷"
]),
});


int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<50 )
                return notify_fail("你的內力修為不夠。\n");

        if ((int)me->query_skill("force") < 10)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("kuimang-dao", 1))
                return notify_fail("你的基本刀法水平有限，無法領會更高深的□蟒刀法。\n");

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
        level = (int) me->query_skill("kuimang-dao", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<60 )
                return notify_fail("你的體力不夠練□蟒刀法。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練□蟒刀法。\n");

        me->receive_damage("qi", 45);
        addn("neili", -43, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"kuimang-dao/" + action;
}