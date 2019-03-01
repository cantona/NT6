// tianzhu-fuzhi.c 天竺拂指

inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "$N側身抬臂，右指劃了個半圈，輕輕拂向向$n$l，不著力道",
        "force" : 100,
        "attack": 10,
        "parry" : 15,
        "dodge" : -5,
        "lvl"   : 0,
        "damage_type" : "點穴"
]),
([      "action": "$N左掌虛托，右手中指穿腋疾出，輕拂$n胸前的諸多要穴",
        "force" : 140,
        "attack": 15,
        "parry" : 18,
        "dodge" : -5,
        "lvl"   : 20,
        "damage_type" : "點穴"
]),
([      "action": "$N俯身斜倚，左手半推，右手中指和食指向$n的$l輕輕拂過",
        "force" : 170,
        "attack": 20,
        "parry" : 25,
        "dodge" : 5,
        "lvl"   : 40,
        "damage_type" : "點穴"
]),
([      "action": "$N雙目微睜，雙手十指幻化出千百個指影，拂向$n的$l",
        "force" : 210,
        "attack": 28,
        "parry" : 30,
        "dodge" : 5,
        "damage": 10,
        "lvl"   : 60,
        "damage_type" : "點穴"
]),
([      "action": "只見$N左掌護住丹田，右手斜指蒼天，蓄勢點向$n的$l",
        "force" : 250,
        "attack": 30,
        "parry" : 35,
        "dodge" : 15,
        "damage": 10,
        "lvl"   : 80,
        "damage_type" : "點穴"
]),
});

string main_skill() { return "canhe-zhi"; }

int valid_enable(string usage) { return usage == "finger" ||  usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("canhe-zhi", 1))
                return notify_fail("你已將這種指法融入參合指，不必再分開練習了。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練天竺拂指必須空手。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功火候不夠，無法學天竺拂指。\n");

        if ((int)me->query_skill("finger", 1) < 10)
                return notify_fail("你的基本指法火候不夠，無法學天竺拂指。\n");

        if( query("max_neili", me)<300 )
                return notify_fail("你的內力太弱，無法練天竺拂指。\n");

        if (me->query_skill("finger", 1) < me->query_skill("tianzhu-fuzhi", 1))
                return notify_fail("你的基本指法太差，無法領會更高深的天竺拂指。\n");

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
        level = (int) me->query_skill("tianzhu-fuzhi",1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)me->query_skill("canhe-zhi", 1))
                return notify_fail("你已將這種指法融入參合指，不必再分開練習了。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力太低了，無法練天竺拂指。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠，無法練天竺拂指。\n");

        me->receive_damage("qi", 55);
        addn("neili", -51, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tianzhu-fuzhi/" + action;
}