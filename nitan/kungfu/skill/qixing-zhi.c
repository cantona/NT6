// qixing-zhi.c 七星指

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N一指點出，這一招「朝拜天罡」中宮直進，指氣將$n壓得揣不過氣來",
        "force" : 90,
        "dodge" : 5,
        "damage": 15,
        "lvl"   : 0,
        "damage_type" : "點穴",
        "skill_name"  : "朝拜天罡"
]),
([      "action": "$N身形不動，一招「七星匯聚」攻出。$n稍一猶豫，$N的中指已刺向自己",
        "force" : 140,
        "attack": 5,
        "parry" : 5,
        "dodge" : 5,
        "damage": 20,
        "lvl"   : 40,
        "damage_type" : "點穴",
        "skill_name"  : "七星匯聚"
]),
([      "action": "只見$N一轉身，正是一式「橫移北斗」，一指由脅下穿出，疾刺$n的$l",
        "force" : 155,
        "attack": 10,
        "parry" : 7,
        "dodge" : 5,
        "damage": 30,
        "lvl"   : 40,
        "damage_type" : "點穴",
        "skill_name"  : "橫移北斗"
]),
([      "action": "只見$N一招「偏花七星」，十指如穿花蝴蝶一般上下翻飛，全全籠罩$n",   
        "force" : 170,
        "attack": 20,
        "parry" : 11,
        "dodge" : 9,
        "damage": 40,
        "lvl"   : 60,
        "damage_type" : "點穴",
        "skill_name"  : "偏花七星"
]),
([      "action": "只見$N面帶微笑，負手而立，一招「彗星飛墜」，$n頓覺一道指力直撲而來",
        "force" : 190,
        "attack": 30,
        "parry" : 12,
        "dodge" : 10,
        "damage": 50,
        "lvl"   : 80,
        "damage_type" : "點穴",
        "skill_name"  : "彗星飛墜"
]),
([      "action": "忽聽$N一聲輕叱，一招「滿天星辰」，左手劃了個半弧，食指閃電般點向$n",
        "force" : 250,
        "attack": 40,
        "parry" : 23,
        "dodge" : 25,
        "damage": 57,
        "lvl"   : 100,
        "damage_type" : "點穴",
        "skill_name"  : "滿天星辰"
]),
});

string main_skill() { return "canhe-zhi"; }

int valid_enable(string usage) { return usage == "finger" ||  usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("canhe-zhi", 1))
                return notify_fail("你已將這種指法融入參合指，不必再分開練習了。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練七星指必須空手。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候不夠，無法學七星指。\n");

        if ((int)me->query_skill("finger", 1) < 80)
                return notify_fail("你的基本指法火候不夠，無法學七星指。\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("你的內力太弱，無法練七星指。\n");

        if (me->query_skill("finger", 1) < me->query_skill("qixing-zhi", 1))
                return notify_fail("你的基本指法太差，無法領會更高深的七星指。\n");

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
        level = (int)me->query_skill("qixing-zhi", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)me->query_skill("canhe-zhi", 1))
                return notify_fail("你已將這種指法融入參合指，不必再分開練習了。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力太低了，無法練七星指。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠，無法練七星指。\n");

        me->receive_damage("qi", 55);
        addn("neili", -51, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"qixing-zhi/" + action;
}