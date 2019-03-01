// This is player's own skill (Write by Lonely@nt2)
// Create by 劍明(Jianmin) at Tue Oct 21 16:53:53 2008
// 飛天御劍(fly-sword.c)

#include <ansi.h>
inherit SKILL;        
                
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
([      "action" : "亂擊術,以比肉眼更快的速度向對手亂擊.",
        "attack" : 260,
        "damage" : 260,
        "force" : 260,
        "dodge" : 260,
        "parry" : 260,
        "lvl" : 100,
        "damage_type" : "刺傷",
        "skill_name" : "龍巢閃"
 ]),
// ZHAOSHI : 1
});

int valid_learn(object me)
{
        object weapon; 
        
        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
                
        if( query("max_neili", me)<50 )
                return notify_fail("你的內力太弱，無法練" + "飛天御劍" + "。\n");
                
        return 1;
}

int valid_enable(string usage) { 
        return usage == "sword" || 
               usage == "parry"; 
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("fly-sword",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

mixed *query_actions() { return action; }

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if( query_temp("weapon", me) )
                return 0;

        lvl = me->query_skill("fly-sword", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

int practice_skill(object me)
{
        object weapon; 
        if( !objectp(weapon=query_temp("weapon", me)) || 
                query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");        
        
        if( query("qi", me)<25 )
                return notify_fail("你的體力不夠了，休息一下再練吧。\n");
                
        if( query("neili", me)<3 )
                return notify_fail("你的內力不夠了，休息一下再練吧。\n");
                
        me->receive_damage("qi", 25);
        addn("neili", -3, me);
        return 1;
} 

mixed hit_ob(object me, object victim, int damage)
{
        mixed result;
        if (damage < 100) return 0;

        if (random(damage) > victim->query_str()) 
        {
                result = ([ "damage" : damage ]);
                result += ([ "msg" : HIW "你聽到「喀嚓」一聲輕響，已被$N的兵器所發殺氣挫傷，$n頓時血冒三丈！！！\n" NOR ]);

                return result;
        }
}

string perform_action_file(string action) 
{
        return __DIR__ + "fly-sword" + "/" + action; 
}
string query_description()
{
        return
 "" ; 
}