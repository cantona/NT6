#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N使一招「奔流直下」，右掌一翻，向$n的$l拍去",
        "force"  : 55,
        "attack" : 4,
        "dodge"  : 30,
        "parry"  : 25,       
        "damage" : 20, 
        "lvl"    : 0,
        "damage_type" : "瘀傷",
        "skill_name"  : "奔流直下",
]),
([      "action" : "$N使一招「力擋群山」，右手斜出，劈向$n的$l",
        "force"  : 68,
        "attack" : 6,
        "dodge"  : 48,
        "parry"  : 30,        
        "damage" : 30, 
        "lvl"    : 25,
        "damage_type" : "瘀傷",
        "skill_name"  : "力擋群山",
]),
([      "action" : "$N雙手帶風，一式「單刀附會」，掌力渾厚，擊向$n的$l",
        "force"  : 78,
        "attack" : 10,
        "dodge"  : 50,
        "parry"  : 60,        
        "damage" : 38, 
        "lvl"    : 50,
        "damage_type" : "瘀傷",
        "skill_name"  : "單刀附會", 
]),
([      "action" : "$N雙手微抬，左右齊出，一招「水中探月」，已將$n$l籠罩",
        "force"  : 86,
        "attack" : 12,
        "dodge"  : 44,
        "parry"  : 71,      
        "damage" : 45, 
        "lvl"    : 70,
        "damage_type" : "瘀傷",
         "skill_name" : "水中探月",
]),
([      "action" : "$N雙掌翻騰，掌風凌厲，一式「春風細雨」，飄然不定，擊向$n$l",
        "force"  : 100,
        "attack" : 15,
        "dodge"  : 55,
        "parry"  : 60,       
        "damage" : 50, 
        "lvl"    : 90,
        "damage_type" : "瘀傷",
        "skill_name"  : "春風細雨",
]),
([      "action" : "$N雙掌拍出，一式「雙管齊下」，掌法一快一慢，向$n的$l打去",
        "force"  : 125,
        "attack" : 15,
        "dodge"  : 60,
        "parry"  : 55, 
        "damage" : 55,        
        "lvl"    : 100,
        "damage_type" : "瘀傷",
        "skill_name"  : "雙管齊下",
]),
([      "action" : "$N快步向前，身法陡快，一招「秋卷落葉」，掌風已到$n$l",
        "force"  : 140,
        "attack" : 18,
        "dodge"  : 80,
        "parry"  : 71, 
        "damage" : 63,     
        "lvl"    : 110,
        "damage_type" : "瘀傷",
        "skill_name"  : "秋卷落葉",
]),
([      "action" : "$N雙掌下垂，似是無力，但又猛然加快，似攻非攻，一式「人海孤鴻」\n"
                   "使出，雙掌已到$n$l",
        "force"  : 155,
        "attack" : 25,
        "dodge"  : 76,
        "parry"  : 80,   
        "damage" : 80,    
        "lvl"    : 120,
        "damage_type" : "瘀傷",
        "skill_name"  : "人海孤鴻",
]),
});

int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練孤鴻掌法必須空手。\n");

        if ((int)me->query_skill("force") < 40)
                return notify_fail("你的內功火候不夠，無法學孤鴻掌法。\n");

        if( query("max_neili", me)<120 )
                return notify_fail("你的內力太弱，無法練孤鴻掌法。\n");

        if ((int)me->query_skill("strike", 1) < 30)
                return notify_fail("你的基本掌法火候太淺。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("guhong-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的孤鴻掌法。\n");

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
        level = (int) me->query_skill("guhong-zhang", 1);
        for (i = sizeof(action); i > 0; i--)
            if (level > action[i-1]["lvl"])
                return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠練孤鴻掌法。\n");

        me->receive_damage("qi", 45);
        addn("neili", -40, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"guhong-zhang/" + action;
}