#include <ansi.h>
inherit SKILL;

int is_ultimate_skill() { return 1; }

mapping *action = ({
([      "action" : "$N深吸一口氣，舉起手中$w砍向$n，刀光在空中劃出一道弧線",
        "force"  : 20,
        "attack" : 50,
        "dodge"  : 10,
        "parry"  : 30,
        "lvl"    : 0,
        "damage" : 30,
        "damage_type" : "砍傷",
]),
([      "action" : "$N反手一刀，刀光劃向$n，姿勢優美之極",
        "force"  : 40,
        "attack" : 65,
        "dodge"  : 10,
        "parry"  : 45,
        "lvl"    : 10,
        "damage" : 50,
        "damage_type" : "割傷",
]),
([      "action" : "$N從容不迫，轉動著手中$w，漸漸將$n籠罩",
        "force"  : 80,
        "attack" : 80,
        "dodge"  : 10,
        "parry"  : 55,
        "lvl"    : 20,
        "damage" : 60,
        "damage_type" : "割傷",
]),
});

int valid_enable(string usage)
{
        return usage == "blade" || usage == "parry";
}

int valid_learn(object me)
{
        if ((int)me->query_skill("blade", 1) < 10 )
                return notify_fail("你的基本刀法水平有限，無法練習絕刀\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("juedao", 1))
                return notify_fail("你的基本刀法水平有限，無法領會更高深的絕刀\n");

        return 1;
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
      level = (int) me->query_skill("juedao", 1); 
      for (i = sizeof(action); i > 0; i--) 
              if (level > action[i-1]["lvl"]) 
                      return action[NewRandom(i, 20, level / 5)]; 
    
} 

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<20 )
                return notify_fail("你的體力不夠，無法繼續練習。\n");

        me->receive_damage("qi", 15);

        return 1;
}
