#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N一指點出，這一招「鯨蛟相搏」中宮直進，指氣將$n壓得揣不過氣來",
        "force" : 41,
        "attack": 1,
        "parry" : 3,
        "dodge" : 5,
        "damage": 1,
        "lvl"   : 0,
        "damage_type" : "點穴",
        "skill_name"  : "鯨蛟相搏"
]),
([      "action": "$N身形不動，一招「翻江倒海」攻出。$n稍一猶豫，$N的中指已刺向自己",
        "force" : 49,
        "attack": 3,
        "parry" : 4,
        "dodge" : 7,
        "damage": 2,
        "lvl"   : 10,
        "damage_type" : "點穴",
        "skill_name"  : "翻江倒海"
]),
([      "action": "只見$N一轉身，正是一式「龍騰萬里」，一指由脅下穿出，疾刺$n的$l",
        "force" : 55,
        "attack": 6,
        "parry" : 7,
        "dodge" : 5,
        "damage": 4,
        "lvl"   : 20,
        "damage_type" : "點穴",
        "skill_name"  : "龍騰萬里"
]),
([      "action": "只見$N一招「巨浪滔天」，十指如穿花蝴蝶一般上下翻飛，全全籠罩$n",   
        "force" : 71,
        "attack": 5,
        "parry" : 11,
        "dodge" : 19,
        "damage": 4,
        "lvl"   : 30,
        "damage_type" : "點穴",
        "skill_name"  : "巨浪滔天"
]),
([      "action": "只見$N面帶微笑，負手而立，一招「遙觀滄海」，$n頓覺一道指力直撲而來",
        "force" : 90,
        "attack": 8,
        "parry" : 12,
        "dodge" : 10,
        "damage": 7,
        "lvl"   : 40,
        "damage_type" : "點穴",
        "skill_name"  : "遙觀滄海"
]),
([      "action": "忽聽$N一聲輕叱，一招「滄海一粟」，左手劃了個半弧，食指閃電般點向$n",
        "force" : 110,
        "attack": 12,
        "parry" : 23,
        "dodge" : 25,
        "damage": 9,
        "lvl"   : 50,
        "damage_type" : "點穴",
        "skill_name"  : "滄海一粟"
]),
});

int valid_enable(string usage) { return usage == "finger" ||  usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練滄浪指法必須空手。\n");

        if ((int)me->query_skill("force") < 10)
                return notify_fail("你的內功火候不夠，無法學滄浪指法。\n");

        if ((int)me->query_skill("finger", 1) < 10)
                return notify_fail("你的指法火候不夠，無法學滄浪指法。\n");

        if( query("max_neili", me)<50 )
                return notify_fail("你的內力修為太弱，無法練滄浪指法。\n");

        if (me->query_skill("finger", 1) < me->query_skill("canglang-zhi", 1))
                return notify_fail("你的基本指法太差，無法領會更高深的滄浪指法。\n");

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
        level = (int)me->query_skill("canglang-zhi", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了，無法練滄浪指法。\n");

        if( query("neili", me)<40 )
                return notify_fail("你的內力不夠，無法練滄浪指法。\n");

        me->receive_damage("qi", 25);
        addn("neili", -35, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"canglang-zhi/" + action;
}