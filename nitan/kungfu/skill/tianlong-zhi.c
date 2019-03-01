#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N右手中指斜指而出，一招「天山指」已襲向$n$l",
        "force" : 90,
        "dodge" : 5,
        "damage": 15,
        "lvl"   : 0,
        "damage_type" : "點穴",
        "skill_name" : "天龍式"
]),
([      "action": "$N飛身而起，左手食指一伸，一式「六絕指」罩向$n要穴",
        "force" : 140,
        "attack": 5,
        "parry" : 5,
        "dodge" : 5,
        "damage": 20,
        "lvl" : 40,
        "damage_type" : "點穴",
        "skill_name" : "天龍式"
]),
([      "action": "$N化掌為指，右手無名指連連指出，一股氣流襲向$n$l",
        "force" : 155,
        "attack": 10,
        "parry" : 7,
        "dodge" : 5,
        "damage": 30,
        "lvl"   : 40,
        "damage_type" : "點穴",
        "skill_name" : "天龍式"
]),
([      "action": "$N縱身而起，雙手成指一式「天龍式」猛地指向$n$l",
        "force" : 220,
        "attack": 40,
        "parry" : 21,
        "dodge" : 15,
        "damage": 55,
        "lvl"   : 100,
        "damage_type" : "點穴",
        "skill_name" : "天龍式"
]),
});

string main_skill() { return "canhe-zhi"; }

int valid_enable(string usage) { return usage == "finger" ||  usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("canhe-zhi", 1))
                return notify_fail("你已將這種指法融入參合指，不必再分開練習了。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("大天龍指必須空手。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，無法學大天龍指。\n");

        if ((int)me->query_skill("finger", 1) < 40)
                return notify_fail("你的基本指法火候不夠，無法學大天龍指。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力太弱，無法練大天龍指。\n");

        if (me->query_skill("finger", 1) < me->query_skill("tianlong-zhi", 1))
                return notify_fail("你的基本指法太差，無法領會更高深的大天龍指。\n");

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
        level = (int)me->query_skill("tianlong-zhi", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)me->query_skill("canhe-zhi", 1))
                return notify_fail("你已將這種指法融入參合指，不必再分開練習了。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力太低了，無法練大天龍指。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠，無法練大天龍指。\n");

        me->receive_damage("qi", 55);
        addn("neili", -51, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tianlong-zhi/" + action;
}
