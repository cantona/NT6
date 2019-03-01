#include <ansi.h> 
inherit SHAOLIN_SKILL; 

mapping *action = ({ 
([      "action": "$N棍勢連綿，著著俱是進攻招式，手中$w一連幾棍，劈頭蓋臉地朝著$n砸下", 
        "dodge" : 30, 
        "attack": 33, 
        "force" : 89, 
        "damage": 34, 
        "parry" : 35, 
        "lvl" : 0, 
        "damage_type": "砸傷" 
]),
([      "action": "$N點、紮、纏、掃、棍風呼呼，攻勢極為凌厲，舞起一團棍影齊齊罩向$n", 
        "dodge" : 35, 
        "attack": 33, 
        "force" : 116, 
        "damage": 52, 
        "parry" : 44, 
        "lvl" : 30, 
        "damage_type": "砸傷" 
]),
([      "action": "$N哈哈大笑，單手提棍，手中$w閃電般的直襲而出，砸向$n$l", 
        "dodge" : 48, 
        "attack": 48, 
        "force" : 136, 
        "damage": 78, 
        "parry" : 40, 
        "lvl" : 60, 
        "damage_type": "砸傷" 
]),
([      "action": "$N大喝一聲，手中$w高高舉起，掛著風聲劈頭蓋臉的砸向$n的$l", 
        "dodge" : 40, 
        "attack": 58, 
        "force" : 200, 
        "damage": 100, 
        "parry" : 22, 
        "lvl" : 90, 
        "damage_type": "砸傷" 
]), 
([      "action": "$N撲身上前，手中$w驟然加緊，剎那間幻起十幾條棍影，漫天飛舞，左右繚繞攻到$n的$l", 
        "dodge" : 36, 
        "attack": 66, 
        "force" : 234, 
        "damage": 101, 
        "parry" : 31, 
        "lvl" : 120, 
        "damage_type": "砸傷" 
]),
([      "action": "$N縱身躍起，手中$w轉得如車輪一般，一棒化數棒直擊$n頂門", 
        "dodge" : 35, 
        "attack": 80, 
        "force" : 273, 
        "damage": 104, 
        "parry" : 35, 
        "lvl" : 150, 
        "damage_type": "砸傷" 
]), 
}); 

int valid_enable(string usage) 
{
        return usage == "parry" || usage == "club"; 
}

int valid_learn(object me) 
{
        object weapon; 

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "club" )
                return notify_fail("你必須先找一根棍子才能練夜叉棍法。\n"); 

        if( query("max_neili", me)<500 )
                return notify_fail("你的內力不足，難以修煉夜叉棍法。\n"); 


        if ((int)me->query_skill("force") < 100) 
                return notify_fail("你的內功火候太淺，難以修煉夜叉棍法。\n"); 

        if ((int)me->query_skill("club", 1) < 100) 
                return notify_fail("你的基本棍法火候太淺，難以修煉夜叉棍法。\n"); 

        if ((int)me->query_skill("club", 1) < (int)me->query_skill("yecha-gun", 1)) 
                return notify_fail("你的基本棍法水平不夠，無法領會更高深的夜叉棍法。\n"); 
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
        level = (int) me->query_skill("yecha-gun",1); 
        for (i = sizeof(action); i > 0; i--) 
                if (level > action[i-1]["lvl"]) 
                        return action[NewRandom(i, 20, level / 5)]; 
}

int practice_skill(object me) 
{
        object weapon; 

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "club" )
               return notify_fail("你使用的武器不對。\n"); 

        if( query("qi", me)<70 )
               return notify_fail("你的體力不夠。\n"); 

        if( query("neili", me)<60 )
               return notify_fail("你的內力不夠。\n"); 

        me->receive_damage("qi", 55); 
        addn("neili", -45, me);
        return 1; 
} 

string perform_action_file(string action) 
{ 
        return __DIR__"yecha-gun/" + action; 
}
