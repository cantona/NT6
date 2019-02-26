// huanyin-zhi.c

inherit SKILL;

mapping *action = ({
([      "action": "$N一直戳出，幻起一團指影，逼向$n的$l",
        "force" : 250,
        "attack": 19,
        "parry" : 22,
        "dodge" : 18,
        "damage": 28,
        "lvl"   : 0,
        "damage_type" : "刺傷"
]),
([      "action": "$N全身之力聚於一指，直指向$n的胸前",
        "force" : 270,
        "attack": 36,
        "parry" : 31,
        "dodge" : 28,
        "damage": 35,
        "lvl"   : 30,
        "skill_name" : "天似無情",
        "damage_type" : "刺傷"
]),
([      "action": "$N提身卻步，右手忽的點出，向$n的$l劃過",
        "force" : 290,
        "attack": 39,
        "parry" : 22,
        "dodge" : 38,
        "damage": 45,
        "lvl"   : 60,
        "skill_name" : "情根深種",
        "damage_type" : "刺傷"
]),
([      "action": "$N輕聲吐氣，雙指飛似的刺向$n的額、頸、肩、臂、胸、背",
        "force" : 300,
        "attack": 47,
        "parry" : 42,
        "dodge" : 35,
        "damage": 48,
        "lvl"   : 90,
        "skill_name" : "情在天涯",
        "damage_type" : "刺傷"
]),
([      "action": "$N左掌掌心向外，右指蓄勢點向$n的$l",
        "force" : 330,
        "attack": 55,
        "parry" : 50,
        "dodge" : 48,
        "damage": 55,
        "lvl"   : 120,
        "skill_name" : "獨飲情傷",
        "damage_type" : "刺傷"
]),
([      "action": "$N右手伸出，十指叉開，小指拂向$n的太淵穴",
        "force" : 350,
        "attack": 70,
        "parry" : 60,
        "dodge" : 58,
        "damage": 60,
        "lvl"   : 150,
        "skill_name" : "無訴別情",
        "damage_type" : "刺傷"
]),
});

int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }


int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練幻陰指法必須空手。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功火候不夠，無法學幻陰指法。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的內力太弱，無法練幻陰指法。\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("huanyin-zhi", 1))
                return notify_fail("你的基本指法水平有限，無法領會更高深的幻陰指法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("huanyin-zhi",1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<80 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<75 )
                return notify_fail("你的內力不夠練幻陰指法。\n");

        me->receive_damage("qi", 72);
        addn("neili", -69, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"huanyin-zhi/" + action;
}