#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N使一招「天馬行空」，右掌一翻，向$n的$l拍去",
        "force"  : 90,
        "attack" : 4,
        "dodge"  : 30,
        "parry"  : 25,       
        "damage" : 25, 
        "lvl"    : 0,
        "damage_type" : "瘀傷",
        "skill_name"  : "天馬行空",
]),
([      "action" : "$N使一招「探手截流」，右手斜出，劈向$n的$l",
        "force"  : 110,
        "attack" : 6,
        "dodge"  : 48,
        "parry"  : 30,        
        "damage" : 40, 
        "lvl"    : 25,
        "damage_type" : "瘀傷",
        "skill_name"  : "探手截流",
]),
([      "action" : "$N雙手帶風，一式「風吹雲散」，掌力渾厚，擊向$n的$l",
        "force"  : 120,
        "attack" : 10,
        "dodge"  : 50,
        "parry"  : 60,        
        "damage" : 48, 
        "lvl"    : 50,
        "damage_type" : "瘀傷",
        "skill_name"  : "風吹雲散", 
]),
([      "action" : "$N雙手微抬，左右齊出，一招「雲深霧鎖」，已將$n$l籠罩",
        "force"  : 150,
        "attack" : 12,
        "dodge"  : 44,
        "parry"  : 71,      
        "damage" : 55, 
        "lvl"    : 70,
        "damage_type" : "瘀傷",
         "skill_name" : "雲深霧鎖",
]),
([      "action" : "$N雙掌翻騰，掌風凌厲，一式「雲霧繚繞」，飄然不定，擊向$n$l",
        "force"  : 180,
        "attack" : 15,
        "dodge"  : 55,
        "parry"  : 60,       
        "damage" : 60, 
        "lvl"    : 90,
        "damage_type" : "瘀傷",
        "skill_name"  : "雲霧繚繞",
]),
([      "action" : "$N雙掌拍出，一式「順流逆流」，掌法一快一慢，向$n的$l打去",
        "force"  : 210,
        "attack" : 15,
        "dodge"  : 60,
        "parry"  : 62, 
        "damage" : 70,        
        "lvl"    : 100,
        "damage_type" : "瘀傷",
        "skill_name"  : "順流逆流",
]),
([      "action" : "$N快步向前，身法陡快，一招「行雲流水」，掌風已到$n$l",
        "force"  : 240,
        "attack" : 18,
        "dodge"  : 80,
        "parry"  : 71, 
        "damage" : 80,     
        "lvl"    : 110,
        "damage_type" : "瘀傷",
        "skill_name"  : "行雲流水",
]),
([      "action" : "$N雙掌下垂，似是無力，但又猛然加快，似攻非攻，一式「流水無情」\n"
                   "使出，雙掌已到$n$l",
        "force"  : 280,
        "attack" : 25,
        "dodge"  : 76,
        "parry"  : 80,   
        "damage" : 90,    
        "lvl"    : 120,
        "damage_type" : "瘀傷",
        "skill_name"  : "流水無情",
]),
});

int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練流雲掌必須空手。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候不夠，無法學流雲掌。\n");

        if( query("max_neili", me)<500 )
                return notify_fail("你的內力太弱，無法練流雲掌。\n");

        if ((int)me->query_skill("strike", 1) < 80)
                return notify_fail("你的基本掌法火候太淺。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("liuyun-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的流雲掌。\n");

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
        level = (int) me->query_skill("liuyun-zhang", 1);
        for (i = sizeof(action); i > 0; i--)
            if (level > action[i-1]["lvl"])
                return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<80 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練流雲掌。\n");

        me->receive_damage("qi", 65);
        addn("neili", -60, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"liuyun-zhang/" + action;
}