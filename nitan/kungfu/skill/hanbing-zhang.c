#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N使一招「冰封萬里」，右掌一翻，向$n的$l拍去",
        "force"  : 90,
        "attack" : 4,
        "dodge"  : 30,
        "parry"  : 25,       
        "damage" : 25, 
        "lvl"    : 0,
        "damage_type" : "瘀傷",
        "skill_name"  : "冰封萬里",
]),
([      "action" : "$N使一招「不寒而慄」，左手猛地拍向$n的$l",
        "force"  : 110,
        "attack" : 6,
        "dodge"  : 48,
        "parry"  : 30,        
        "damage" : 40, 
        "lvl"    : 25,
        "damage_type" : "瘀傷",
        "skill_name"  : "不寒而慄",
]),
([      "action" : "$N雙目微閉，一式「冰凍三尺」，掌力渾厚，擊向$n的$l",
        "force"  : 120,
        "attack" : 10,
        "dodge"  : 50,
        "parry"  : 60,        
        "damage" : 48, 
        "lvl"    : 50,
        "damage_type" : "瘀傷",
        "skill_name"  : "冰凍三尺", 
]),
([      "action" : "$N雙手微抬，左右齊出，一招「水火不容」，已將$n$l籠罩",
        "force"  : 150,
        "attack" : 12,
        "dodge"  : 44,
        "parry"  : 71,      
        "damage" : 55, 
        "lvl"    : 70,
        "damage_type" : "瘀傷",
         "skill_name" : "水火不容",
]),
([      "action" : "$N雙掌翻騰，卻欲停止，一式「萬里雪飄」，飄然不定，擊向$n$l",
        "force"  : 180,
        "attack" : 15,
        "dodge"  : 55,
        "parry"  : 60,       
        "damage" : 60, 
        "lvl"    : 90,
        "damage_type" : "瘀傷",
        "skill_name"  : "萬里雪飄",
]),
([      "action" : "$N單掌直出，內勁十足，一式「寒冰無極」，掌法一快一慢，向$n的$l打去",
        "force"  : 210,
        "attack" : 15,
        "dodge"  : 60,
        "parry"  : 62, 
        "damage" : 70,        
        "lvl"    : 100,
        "damage_type" : "瘀傷",
        "skill_name"  : "寒冰無極",
]),
([      "action" : "$N快步踏出，雙掌暗自運勁，一招「冰天雪地」，掌風已到$n$l",
        "force"  : 240,
        "attack" : 18,
        "dodge"  : 80,
        "parry"  : 71, 
        "damage" : 80,     
        "lvl"    : 110,
        "damage_type" : "瘀傷",
        "skill_name"  : "冰天雪地",
]),
([      "action" : "$N左掌忽地拍向$n，又突然收回，緊跟着右掌斜出，一招「"
                   "天寒地凍」劈向$n$l",
        "force"  : 280,
        "attack" : 25,
        "dodge"  : 76,
        "parry"  : 80,   
        "damage" : 90,    
        "lvl"    : 120,
        "damage_type" : "瘀傷",
        "skill_name"  : "天寒地凍",
]),
});

int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練寒冰掌必須空手。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候不夠，無法學寒冰掌。\n");

        if( query("max_neili", me)<600 )
                return notify_fail("你的內力太弱，無法練寒冰掌。\n");

        if ((int)me->query_skill("strike", 1) < 100)
                return notify_fail("你的基本掌法火候太淺。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("hanbing-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的寒冰掌。\n");

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
        level = (int) me->query_skill("hanbing-zhang", 1);
        for (i = sizeof(action); i > 0; i--)
            if (level > action[i-1]["lvl"])
                return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<80 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練寒冰掌。\n");

        me->receive_damage("qi", 65);
        addn("neili", -60, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"hanbing-zhang/" + action;
}