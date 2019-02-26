//幻魔身法。花間派輕功。

#include <ansi.h>
inherit SKILL;


mapping *action = ({
([      "action" : "$n身形左閃右晃，姿勢瀟灑之極，一招[輕靈幻香]輕巧地躲開$N的進攻。"
]),
([      "action" : "$n宛如一屢青煙，飄忽不定，令人琢磨不定，一招[無魔無形]閃到了$N的身後。"
]),
([      "action" : "$n姿態幽雅之極，躲閃之中絲毫不顯狼狽之態，一招[凌波漣漣]避開了$N的攻擊。!"
]),
([      "action" : "$n身形突然連晃數下，宛如雲霧中的幻靈，一招[霧裏藏花]躲開了$N的攻擊。"
])

});

mapping query_action(object me)
{
	

	return action[random(sizeof(action))];
}


int valid_learn(object me)
{
    
	   return 1;
}



int practice_skill(object me)
{
     
	
	return 1;
}

string query_type()
{
	return "dodge";
}
string query_base()
{
	return "dodge";
}

int query_dodge(object me)
{
	return 100;
}