#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N使一招「只手攬月」，左手斜出，一拳向$n的$l打去",
        "force"  : 10,
        "dodge"  : 30,
        "parry"  : 25,       
        "lvl"    : 0,
        "damage_type" : "瘀傷",
        "skill_name"  : "只手攬月",
]),
([      "action" : "$N使一招「只手攬日」，右手揮出，劈向$n的$l",
        "force" : 25,
        "dodge" : 48,
        "parry" : 30,        
        "lvl"   : 10,
        "damage_type" : "瘀傷",
        "skill_name"  : "只手攬日",
]),
([      "action" : "$N雙手回撤，忽地反轉，一式「風迎紫煙」，擊向$n的$l",
        "force"  : 35,
        "dodge"  : 50,
        "parry"  : 45,        
        "lvl"    : 20,
        "damage_type" : "瘀傷",
        "skill_name"  : "風迎紫煙", 
]),
([      "action" : "$N雙手分開，左右齊出，一招「水火不容」，分擊$n的面門和$l",
        "force" : 42,
        "dodge" : 44,
        "parry" : 71,      
        "lvl"   : 30,
        "damage_type" : "瘀傷",
         "skill_name" : "水火不容",
]),
([      "action" : "$N單腳踏出，屈身向前，一式「滿面春風」，擊向$n$l",
        "force"  : 50,
        "dodge"  : 55,
        "parry"  : 60,       
        "lvl"    : 42,
        "damage_type" : "瘀傷",
        "skill_name"  : "滿面春風",
]),
([      "action" : "$N雙手猛然回收，突然右拳直出，一式「縱虎歸山」向$n的$l打去",
        "force"  : 60,
        "dodge"  : 60,
        "parry"  : 62,        
        "lvl"    : 55,
        "damage_type" : "瘀傷",
        "skill_name"  : "縱虎歸山",
]),
([      "action" : "$N快步向前，一招「普天同慶」，左拳直擊$n$l",
        "force"  : 70,
        "dodge"  : 54,
        "parry"  : 71,     
        "lvl"    : 65,
        "damage_type" : "瘀傷",
        "skill_name"  : "普天同慶",
]),
([      "action" : "$N拳風凌厲，拳速猛然變快，一式「殊途同歸」雙拳已到$n$l",
        "force"  : 80,
        "dodge"  : 76,
        "parry"  : 80,       
        "lvl"    : 80,
        "damage_type" : "瘀傷",
        "skill_name"  : "殊途同歸",
]),
});

int valid_enable(string usage)
{
        return usage == "cuff" || usage == "parry";
}

int valid_combine(string combo)
{
        return combo == "biluo-zhang";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練衡山拳法必須空手。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功火候不夠，無法學衡山拳法。\n");

        if( query("max_neili", me)<200 )
                return notify_fail("你的內力修為太弱，無法練衡山拳法。\n");

        if ((int)me->query_skill("cuff", 1) < 20)
                return notify_fail("你的基本拳法火候太淺，無法練衡山拳法。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("henshan-quan", 1))
                return notify_fail("你的基本拳法水平有限，無法領會更高深的衡山拳法。\n");

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
        level = (int) me->query_skill("henshan-quan", 1);
        for (i = sizeof(action); i > 0; i--)
            if (level > action[i-1]["lvl"])
                return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠練衡山拳法。\n");

        me->receive_damage("qi", 45);
        addn("neili", -35, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"henshan-quan/" + action;
}