// This is player's own skill (Write by Lonely@nt2)
//Createby小妖(Sata)atTue May 10 13:11:08 2011
// 靈犀一指指(lingxi-zhi-finger.c)

#include <ansi.h>
inherit SKILL;        
                
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
([      "action" : "$N雙臂微曲，兩拳緊握，一式「靈光乍現」，雙手食指猛的點向$n。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 100,
	"damage_type" : "瘀傷",
	"skill_name" : "靈光乍現"
 ]),
// ZHAOSHI : 1
([      "action" : "$N兩臂緊伸，腿腳尖點地，一式「一指驚天」，雙手劍指緊握對準$n的$l用盡全身力氣戳了上去。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 110,
	"damage_type" : "瘀傷",
	"skill_name" : "一指驚天"
 ]),
// ZHAOSHI : 2
([      "action" : "$N兩臂緊伸，腿腳尖點地，一式「一指定坤」，左手中指直接指向$n的$l",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 120,
	"damage_type" : "瘀傷",
	"skill_name" : "一指定坤"
 ]),
// ZHAOSHI : 3
([      "action" : "$N兩臂緊伸，一式「定江山」，右手大拇指直指$n的$l而去",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 130,
	"damage_type" : "瘀傷",
	"skill_name" : "定江山"
 ]),
// ZHAOSHI : 4
([      "action" : "$N雙掌十指並齊，一式「千軍破」，帶著罡風死死的鎖住$n。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 140,
	"damage_type" : "瘀傷",
	"skill_name" : "千軍破"
 ]),
// ZHAOSHI : 5
});

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練"+"靈犀一指指"+"必須空手。\n");
        if( query("max_neili", me)<50 )
                return notify_fail("你的內力太弱，無法練"+"靈犀一指指"+"。\n");
        return 1;
}

int valid_enable(string usage) { 
        return usage == "finger" || 
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
        level = (int)me->query_skill("lingxi-zhi-finger",1);
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

        lvl = me->query_skill("lingxi-zhi-finger", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

int practice_skill(object me)
{
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
                result += ([ "msg" : HIW "你聽到「喀嚓」一聲輕響，已被$N所發殺氣挫傷，$n頓時血冒三丈！！！\n" NOR ]);

                return result;
        }
}

string perform_action_file(string action) 
{
        return __DIR__ + "lingxi-zhi-finger" + "/" + action; 
}