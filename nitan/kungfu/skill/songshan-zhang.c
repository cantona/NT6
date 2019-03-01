#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N使一招「滾滾長江」，左手斜出，一掌向$n的$l打去",
        "force"  : 10,
        "dodge"  : 30,
        "parry"  : 25,       
        "lvl"    : 0,
        "damage_type" : "瘀傷",
        "skill_name"  : "滾滾長江",
]),
([      "action" : "$N使一招「大江東去」，右手揮出，劈向$n的$l",
        "force" : 25,
        "dodge" : 48,
        "parry" : 30,        
        "lvl"   : 10,
        "damage_type" : "瘀傷",
        "skill_name"  : "大江東去",
]),
([      "action" : "$N雙手回撤，忽地反轉，一式「天日無華」，擊向$n的$l",
        "force"  : 35,
        "dodge"  : 50,
        "parry"  : 45,        
        "lvl"    : 20,
        "damage_type" : "瘀傷",
        "skill_name"  : "天日無華", 
]),
([      "action" : "$N雙手分開，左右齊出，一招「水火不容」，分擊$n的面門和$l",
        "force" : 42,
        "dodge" : 44,
        "parry" : 71,      
        "lvl"   : 30,
        "damage_type" : "瘀傷",
         "skill_name" : "水火不容",
]),
([      "action" : "$N單腳踏出，屈身向前，一式「連綿不絕」，擊向$n$l",
        "force"  : 50,
        "dodge"  : 55,
        "parry"  : 60,       
        "lvl"    : 42,
        "damage_type" : "瘀傷",
        "skill_name"  : "連綿不絕",
]),
([      "action" : "$N雙手猛然回收，突然右掌直出，一式「漫天花雨」向$n的$l打去",
        "force"  : 60,
        "dodge"  : 60,
        "parry"  : 62,        
        "lvl"    : 55,
        "damage_type" : "瘀傷",
        "skill_name"  : "漫天花雨",
]),
([      "action" : "$N快步向前，一招「陽光嬌子」，左掌直擊$n$l",
        "force"  : 70,
        "dodge"  : 54,
        "parry"  : 71,     
        "lvl"    : 65,
        "damage_type" : "瘀傷",
        "skill_name"  : "陽光嬌子",
]),
([      "action" : "$N掌風凌厲，掌速猛然變快，一式「會心一擊」雙掌已到$n$l",
        "force"  : 80,
        "dodge"  : 76,
        "parry"  : 80,       
        "lvl"    : 80,
        "damage_type" : "瘀傷",
        "skill_name"  : "會心一擊",
]),
});

int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_combine(string combo)
{
        return combo == "songshan-quan";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練嵩山掌法必須空手。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功火候不夠，無法學嵩山掌法。\n");

        if( query("max_neili", me)<200 )
                return notify_fail("你的內力修為太弱，無法練嵩山掌法。\n");

        if ((int)me->query_skill("strike", 1) < 20)
                return notify_fail("你的基本掌法火候太淺，無法練嵩山掌法。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("songshan-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的嵩山掌法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
            if (level >= action[i]["lvl"])
                return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("songshan-zhang", 1);
        for (i = sizeof(action); i > 0; i--)
            if (level > action[i-1]["lvl"])
                return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠練嵩山掌法。\n");

        me->receive_damage("qi", 45);
        addn("neili", -35, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"songshan-zhang/" + action;
}