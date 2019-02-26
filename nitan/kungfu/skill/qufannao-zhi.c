//gladiator

#include <ansi.h>
#include <mudlib.h>


inherit SHAOLIN_SKILL;
inherit F_DAMAGE;

mapping *action = ({
        ([
                "action":"$N神色端莊，長吸一口氣，左手食指突然點向$n胸口",
                "force" : 350,
                "dodge" : 30,
                "damage" : 50,
                "parry" : 35,
                "weapon": "無形劍氣",
                "skill_name" :  "無相無色",  
                "lvl" : 10,
                "damage_type" : "刺傷"
                ]),
                ([
                "action":"$N飄然退後，右手中指三曲三伸，一股無形指力猛襲$n下腹",
                "force" : 400,
                "dodge" : 40, 
                "parry" : 30,   
                "damage" : 80,  
                "weapon": "無形劍氣",
                "skill_name" :  "煩惱無劫", 
                "lvl" : 50,
                "damage_type" : "刺傷"
                ]),
                ([
                "action":"$N絲毫不為$n所動，雙手交替中，一式“煩惱無歸”已封住了$n的所有退路",
                "force" : 450,
                "dodge" : 40,
                "parry" : 25,
                "damage": 100,
                "weapon": "無形劍氣",
                "skill_name" :  "煩惱無歸",
                "lvl" : 80,
                "damage_type" : "內傷"
                ]),
                ([      
                "action":"$N中指划動，無形指力瀰漫四周。$n頓時上躥下跳狼狽躲避",
                "force" : 500,
                "dodge" : 50,
                "parry" : 50,
                "damage": 130,
                "weapon": "無形劍氣",
                "skill_name" :  "煩惱無盡",
                "lvl" : 90,
                "damage_type" : "刺傷"
                ]),
                ([
                "action":"$N忽然間化指為掌，“煩惱無形”意味古拙，掌力廣被，$n莫辨其方向，難以招架",
                "force" : 550,
                "dodge" : 55, 
                "damage": 170,
                "weapon": "無形劍氣",
                "skill_name" :  "煩惱無形",
                "lvl" : 60,
                "damage_type" : "內傷"
                ]),
                ([
                "action":"$N俯身前探，右手食指連點數下，已將參和指發揮至極致",
                "force" : 550,
                "dodge" : 55,
                "parry" : 50,
                "damage" : 200,
                "weapon": "無形劍氣",
                "skill_name" :  "煩惱無極",
                "lvl" : 75,
                "damage_type" : "刺傷"
                ]),
                ([      
                "action":"$N遙點數指，卻是半點風聲也無，$n胸口一緊，頓覺遍體冰涼",
                "force" : 580, 
                "dodge" : 60,
                "parry" : 50,
                "damage" : 250,
                "weapon": "無形劍氣",
                "skill_name" :  "煩惱無指",
                "lvl" : 90,
                "damage_type" : "刺傷"
                ]),
});  

int valid_enable(string usage)
{
        return usage == "finger" || usage == "parry";
}

int valid_learn(object me)
{         
        int aa,bb;
        aa = (int)me->query_skill("hunyuan-yiqi",1);
        bb = (int)me->query_skill("qufannao-zhi",1);
        
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練去煩惱指必須空手。\n");
        
        if ( bb  >= 60 && aa < 140 && 5 * aa <= 4 * bb )
                return notify_fail("你的內功不夠，無法修練更高深的去煩惱指。\n");

        if ((int)me->query_skill("finger", 1) <120)
                return notify_fail("你的基本指法火候不夠，無法學去煩惱指。\n");
        return 1;
}


int practice_skill(object me)
{
        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠練去煩惱指。\n");

        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠練去煩惱指。\n");

        addn("neili", -20, me);
        addn("qi", -20, me);
        return 1;

}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("qufannao-zhi", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}


string perform_action_file(string action)
{
    return __DIR__"qufannao-zhi/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        if( random(me->query_skill("qufannao-zhi", 1)) > 80 ) 
        {
                victim->apply_condition("hh_damage",
                random(me->query_skill("qufannao-zhi", 1) / 3) + victim->query_condition("hh_damage"));
        }

        if( query_temp("jinzhongzhao", victim)){
                victim->apply_condition("hh_damage", victim->query_condition("hh_damage") / 3);
        }
}
