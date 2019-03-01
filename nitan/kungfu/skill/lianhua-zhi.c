// lianhua-zhi.c 蓮花指

inherit SKILL;

mapping *action = ({
([      "action": "$N側身抬臂，右指劃了個半圈，一式「臘月開蓮」擊向$n的$l",
        "force" : 100,
        "attack": 10,
        "parry" : 15,
        "dodge" : -5,
        "lvl"   : 0,
        "skill_name" : "臘月開蓮",
        "damage_type" : "刺傷"
]),
([      "action": "$N左掌虛托，一式「蓮蕊璨目」，右指穿腋疾出，指向$n的胸前",
        "force" : 140,
        "attack": 15,
        "parry" : 18,
        "dodge" : -5,
        "lvl"   : 20,
        "skill_name" : "蓮蕊璨目",
        "damage_type" : "刺傷"
]),
([      "action": "$N俯身斜倚，左手半推，右手一式「荷內蓮香」，向$n的$l劃過",
        "force" : 170,
        "attack": 20,
        "parry" : 25,
        "dodge" : 5,
        "lvl"   : 40,
        "skill_name" : "荷內蓮香",
        "damage_type" : "刺傷"
]),
([      "action": "$N雙目微睜，一式「杏蓮九出」，雙手幻化出千百個指影，拂向$n的$l",
        "force" : 210,
        "attack": 28,
        "parry" : 30,
        "dodge" : 5,
        "damage": 10,
        "lvl"   : 60,
        "skill_name" : "杏蓮九出",
        "damage_type" : "刺傷"
]),
([      "action": "$N一式「七寶蓮花」，左掌護住丹田，右手斜指蒼天，蓄勢點向$n的$l",
        "force" : 250,
        "attack": 30,
        "parry" : 35,
        "dodge" : 15,
        "damage": 10,
        "lvl"   : 80,
        "skill_name" : "七寶蓮花",
        "damage_type" : "刺傷"
]),
([      "action": "$N雙掌平托胸前，十指叉開，一式「葉底留蓮」，指向$n的周身大穴",
        "force" : 280,
        "attack": 45,
        "parry" : 40,
        "dodge" : 20,
        "damage": 15,
        "lvl"   : 100,
        "skill_name" : "葉底留蓮",
        "damage_type" : "刺傷"
]),
});

string main_skill() { return "canhe-zhi"; }

int valid_enable(string usage) { return usage == "finger" ||  usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("canhe-zhi", 1))
                return notify_fail("你已將這種指法融入參合指，不必再分開練習了。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練蓮花指必須空手。\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的內功火候不夠，無法學蓮花指。\n");

        if ((int)me->query_skill("finger", 1) < 60)
                return notify_fail("你的基本指法火候不夠，無法學蓮花指。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的內力太弱，無法練蓮花指。\n");

        if (me->query_skill("finger", 1) < me->query_skill("lianhua-zhi", 1))
                return notify_fail("你的基本指法太差，無法領會更高深的蓮花指。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("lianhua-zhi", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)me->query_skill("canhe-zhi", 1))
                return notify_fail("你已將這種指法融入參合指，不必再分開練習了。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力太低了，無法練蓮花指。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠，無法練蓮花指。\n");

        me->receive_damage("qi", 55);
        addn("neili", -51, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"lianhua-zhi/" + action;
}