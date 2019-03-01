//影子劍法.
//中級-->終極武功。

inherit SKILL;
#include <ansi.h>

mapping *action=({
([ "action":"$N身行突然暴起，一招「無影飛劍」以快速無比的速度刺向$n的$l處！",
    "apply_factor": 2,
    "name" : "無影飛劍", 
    "damage_type":"刺傷",
  ]),
 ([ "action":"$N左晃右閃，令人琢磨不定，一招「無影無蹤」突然一劍刺向$n的$l！",
    "apply_factor": 5,
    "name" : "無影無蹤", 
    "damage_type":"刺傷",
  ]),
  ([ "action":"$N聚氣凝神，$w忽然猛地刺向$n的$l，正是一招「天外飛影」！",
    "apply_factor": 10,
    "name" : "天外飛影",
    "damage_type":"刺傷",
  ]),
  ([ "action":"$N的$w忽然化做萬千劍影，從四面八方刺向$n的$l，正是一招「千劍尋命」！",
    "apply_factor": 7,
    "name" : "千劍尋命",
    "damage_type":"刺傷",
  ])});   

string *parry_weapon=({

"$N的$w上充滿了殺氣，完全不顧及自己的身體，拼命一招擋開$n的$v！\n",
"$N手中的$w猶如毒蛇一般，從詭異的角度刺來，迫得$n收回$v！\n",
"$N陰險地一笑，$w劃著詭異的線路擋開了$n的$v。\n",
"$N將全身的力量集中于$w之上，猛地一刺，正好將$n的$v擋開！\n"

});

string *parry_hand=({

"$N的招式詭異無比，猶如鬼魅一般，一招閃電般的招數封住了$n的進攻！\n",
"$N身形猶如毒蛇，招式猶如鬼魅，在$n摸不清動向之際，$N已然用$w封住了$n的進攻！\n",
"$N突然沙啞的一叫，猶如鬼哭狼嚎，手中$w趁機遞出，擋住了$n的進攻。\n",
"$N完全不顧$n的進攻，手中$w一折，刺向$n的額頭，$n一驚，連忙抽身撤了回來！\n"

});

string query_parry_action(object me,object victim)
{
   if(victim->query_temp("weapon"))
    return parry_weapon[random(sizeof(parry_weapon))];
   return parry_hand[random(sizeof(parry_hand))];

}

mapping query_action(object me,object weapon)
{
   return action[random(sizeof(action))];
 
}
mapping *query_all_action(object me)
{
return action;	
}

int practice_skill(object me)  
{
   object weapon;
   
   if(me->query_skill("yingzi-jianfa",1)<200)
    return notify_fail("只有影子劍法達到二百級後才可以練習提高！\n");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不對。\n");
 
 return 1;  
}

string query_type()    
{                      
	return "sword";
}
string query_base()  
{
	return "sword";
}

int valid_learn(object me)
{
	object weapon;
	
	if(me->query("job_office_number/殺手任務")<10)
	 return notify_fail("你的殺手任務功績太低了，還不能學習影子劍法！\n");
	
	if(me->query_skill("yingzi-jianfa",1)>=me->query("job_office_number/殺手任務")*5)
	 return notify_fail("你必須繼續提高殺手任務功績，才能繼續學習影子劍法！\n");
	
	if(!objectp(weapon=me->query_temp("weapon")))
     return notify_fail("手中無劍，如何學習影子劍法？\n");
	 if(weapon->query("skill_type")!="sword")
	return notify_fail("手中無劍，如何學習影子劍法？\n");
	return 1;
}
mapping query_select_action(int i)
{
	if((i)>sizeof(action))
		return 0;
	else return action[i-1];
}


string *query_perform()
{
	return ({"ci","xunming"}); 
}


int skill_damage(object me,object victim)
{
  if(me->query("perform_quest/ci"))
  return 210;
  return 80;
}
