// shedu-qiqiao.c
inherit SKILL;

mapping *action = ({
([      "action" : "$N左指揮出，一式「青蛇挺身」，削向$n的掌緣",
        "force" : 80,
        "dodge" : 5,
        "lvl" : 0,
        "skill_name" : "青蛇挺身",
        "damage_type" : "刺傷"
]),
([      "action" : "$N全身之力聚於一指，一式「銀蛇吐信」，指向$n的胸前",
        "force" : 100,
        "dodge" : 5,
        "lvl" : 15,
        "damage" : 25,
        "skill_name" : "銀蛇吐信",
        "damage_type" : "刺傷"
]),
([      "action" : "$N左掌貼於神道穴，右手一式「金蛇擺尾」，向$n的$l劃過",
        "force" : 120,
        "dodge" : 8,
        "lvl" : 25,
        "damage" : 55,
        "skill_name" : "金蛇擺尾",
        "damage_type" : "刺傷"
]),
([      "action" : "$N雙目怒視，一式「蝮蛇捕食」，雙指拂向$n的額、頸、肩、臂、胸、背",
        "force" : 150,
        "dodge" : 5,
        "damage": 65,
        "lvl" : 45,
        "skill_name" : "蝮蛇捕食",
        "damage_type" : "刺傷"
]),
([      "action" : "$N一式「待機而行」，左掌掌心向外，右指蓄勢點向$n的$l",
        "force" : 180,
        "dodge" : 15,
        "damage": 80,
        "lvl" : 60,
        "skill_name" : "待機而行",
        "damage_type" : "刺傷"
]),
([      "action" : "$N右手伸出，十指叉開，一式「猛蛇出洞」，小指拂向$n的太淵穴",
        "force" : 200,
        "dodge" : 20,
        "damage": 100,
        "lvl" : 70,
        "skill_name" : "猛蛇出洞",
        "damage_type" : "刺傷"
]),
([      "action" : "$N雙迸出無數道勁氣，一式「千蛇纏身」射向$n的全身",
        "force" : 220,
        "dodge" : 25,
        "damage": 120,
        "lvl" : 80,
        "skill_name" : "千蛇纏身",
        "damage_type" : "刺傷"
]),
});

int valid_enable(string usage) { return usage=="finger" || usage=="poison"; }

int valid_combine(string combo) { return combo == "lingshe-quan"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練蛇毒奇巧必須空手。\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的內功火候不夠，無法學蛇毒奇巧。\n");

        if( query("max_neili", me)<350 )
                return notify_fail("你的內力太弱，無法練蛇毒奇巧。\n");

        if ((int)me->query_skill("poison", 1) < 30)
                return notify_fail("你的基本毒技火候不夠，無法學蛇毒奇巧。\n");

        if ((int)me->query_skill("poison", 1) < (int)me->query_skill("shedu-qiqiao", 1))
                return notify_fail("你的基本毒技水平有限，無法領會更高深的蛇毒奇巧。\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("shedu-qiqiao", 1))
                return notify_fail("你的基本指法水平有限，無法領會更高深的蛇毒奇巧。\n");

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
        level = (int) me->query_skill("shedu-qiqiao",1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<55 )
                return notify_fail("你的內力不夠練蛇毒奇巧。\n");

        me->receive_damage("qi", 52);
        addn("neili", -44, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"shedu-qiqiao/" + action;
}