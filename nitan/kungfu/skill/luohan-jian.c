//luohan-jian 羅漢劍法

#include <ansi.h>
inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action" : "$N握緊手中$w一招「來去自如」點向$n的$l",
        "force" : 70,
        "dodge" : 50,
        "damage" : 40,
        "lvl"    : 0,
        "skill_name" : "來去自如", 
        "damage_type" : "刺傷"
]),
([      "action" : "$N一招「日月無光」，無數$w上下刺出，直向$n逼去",
        "force" : 90,
        "dodge" : 20,
        "damage" : 40,
        "lvl"    : 20,
        "skill_name" : "日月無光",
        "damage_type" : "刺傷"
]),
([      "action" : "$N向前跨上一步，手中$w使出「劍氣封喉」直刺$n的喉部",
        "force" : 100,
        "dodge" : 80,
        "damage" : 50,
        "lvl"    : 40,
        "skill_name" : "劍氣封喉",
        "damage_type" : "刺傷"
]),
([      "action" : "$N虛恍一步，使出「心境如水」手中$w直刺$n的要害",
        "force" : 90,
        "dodge" : 60,
        "damage" : 80,
        "lvl"    : 60,
        "skill_name" : "心境如水",
        "damage_type" : "刺傷"
]),
([      "action" : "只見$N掄起手中的$w，使出「佛光普照」萬點金光直射$n",
        "force" : 90,
        "dodge" : 70,
        "damage" : 110,
        "lvl"    : 80,
        "skill_name" : "佛光普照",
        "damage_type" : "刺傷"
]),
([      "action" : "$N掄起手中的$w，使出「風行葉落」無數劍光直射$n",
        "force" : 120,
        "dodge" : 60,
        "damage" : 120,
        "lvl"    : 100,
        "skill_name" : "風行葉落", 
        "damage_type" : "刺傷"
]),
([      "action" : "$N使出「聲東擊西」，手中$w如刮起狂風一般閃爍不定，刺向$n",
        "force" : 200,
        "dodge" : 80,
        "damage" : 140,
        "lvl"    : 120,
        "skill_name" : "聲東擊西",
        "damage_type" : "刺傷"
]),
([      "action" : "$N隨手使出劍法之奧義「無影無蹤」，手中$w如鬼魅一般舖天蓋地的刺向$n",
        "force" : 200,
        "dodge" : 90,
        "damage" : 160,
        "lvl"    : 150,
        "skill_name" : "「無影無蹤」",
        "damage_type" : "刺傷"
]),
([      "action" : HIY"$N使出羅漢劍法之最終絕技「蛟龍出水」手中$w"HIY"猶如蛟龍一般刺向$n "HIY,
        "force" : 280,
        "dodge" : 100,
        "damage" : 180,
        "lvl"    : 220,
        "skill_name" : "HIY「劍氣合一」"NOR,
        "damage_type" : "刺傷"
]),
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); } 

int valid_learn(object me) 

{
        if ((int)me->query_skill("fumo-jian", 1) < 80 
        && (int)me->query_skill("fumo-jian", 1) < 80 
        && (int)me->query_skill("qingliang-jian", 1) < 80) 
                return notify_fail("你的必須先精通伏魔劍，清涼劍中的一種才能繼續學習高深的劍法。\n");  
        if( query("max_neili", me)<650 )
                return notify_fail("你的內力不夠。\n"); 

        if ((int)me->query_skill("force") < 120) 
                return notify_fail("你的內功火候太淺。\n"); 

        if ((int)me->query_skill("sword") < 120)
                return notify_fail("你的基本劍法不夠。\n");                         
        

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("luohan-jian", 1)) 
                return notify_fail("你的基本劍法水平有限，無法領會更高深的羅漢劍法。\n"); 
        return 1; 
} 
string query_skill_name(int level) 
{
        int i; 

        for(i = sizeof(action) - 1; i >= 0; i--) 
                if(level >= action[i]["lvl"]) 
                        return action[i]["skill_name"]; 
}

mapping query_action(object me, object weapon) 
{
        int i, level; 

        level = (int) me->query_skill("luohan-jian", 1); 
        for(i = sizeof(action); i > 0; i--) 
                if(level > action[i-1]["lvl"]) 
                        return action[NewRandom(i, 20, level/5)]; 
}

int practice_skill(object me) 
{ 
        object weapon; 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你必須有把劍才能夠練習羅漢劍。\n"); 

        if( query("qi", me)<70 )
                return notify_fail("你的體力不夠練羅漢劍。\n"); 

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練羅漢劍。\n"); 

        me->receive_damage("qi", 65); 
        addn("neili", -62, me);
        return 1; 
}

string perform_action_file(string action) 
{ 
        return __DIR__"luohan-jian/" + action; 
}
