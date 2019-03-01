#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N手中$w發出“嗖嗖”兩聲，$w斜刺$n$l，正是一招「書聲朗朗」",
        "force"  : 70,
        "dodge"  : 38,
        "parry"  : 25,
        "attack" : 15,
        "damage" : 20,
        "lvl"    : 0,
        "damage_type" : "刺傷",
        "skill_name"  : "書聲朗朗",
]),
([      "action" : "$N$w忽轉，竟向$n的$l刺去，一式「歲歲青蒼」已然使出",
        "force"  : 85,
        "dodge"  : 45,
        "parry"  : 40,
        "attack" : 28,
        "damage" : 30,
        "lvl"    : 25,
        "damage_type" : "刺傷",
        "skill_name"  : "歲歲青蒼",
]),
([     
        "action" : "$N手中$w連續刺出三劍「劍出三生」，分向$n的面門，嚥喉，和$l刺去",
        "force"  : 120,
        "dodge"  : 55,
        "parry"  : 45,
        "attack" : 40,
        "damage" : 38,
        "lvl"    : 50,
        "damage_type" : "刺傷",
        "skill_name"  : "劍出三生",
]),
([      
        "action" : "$N輕嘯一聲，一招「舖天蓋地」，$w挽出一個劍花，劍光四射，洒向$n",
        "force"  : 150, 
        "dodge"  : 65,
        "parry"  : 50,
        "attack" : 45,
        "damage" : 45,
        "lvl"    : 75,
        "damage_type" : "刺傷",
        "skill_name"  : "舖天蓋地",
]),
([      
        "action" : "$N凝神聚氣，猛然一劍刺出，不偏不倚，一招「石廩書聲」直指$n$l",
        "force"  : 180,
        "dodge"  : 80,
        "parry"  : 60,
        "attack" : 55,
        "damage" : 60,
        "lvl"    : 100,
        "damage_type" : "刺傷",
        "skill_name"  : "石廩書聲",
]),
});

string main_skill()
{
        return "wushen-jian";
}

int valid_learn(object me)
{
            object ob;

        if (me->query_skill("wushen-jian", 1) > 0)
                return notify_fail("你已演練合成了衡山五神劍，不必再單獨學習。\n");

            if( !(ob=query_temp("weapon", me) )
            || query("skill_type", ob) != "sword" )
                return notify_fail("你必須先找一把劍才能練劍法。\n");

        if( query("max_neili", me)<400 )
                return notify_fail("你的內力不夠，沒有辦法練石廩劍法。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("sword", 1) < 60)
                   return notify_fail("你的基本劍法火候不夠，無法學習石廩劍法。\n");

        if (me->query_skill("sword", 1) < me->query_skill("shilin-jian", 1))
                return notify_fail("你的基本劍法火候有限，無法領會更高深的石廩劍法。\n");

        return 1;
}

int valid_enable(string usage)
{
            return usage == "sword" || usage == "parry";
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

        level = (int) me->query_skill("shilin-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
       object weapon;

       if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

       if( query("neili", me)<60 )
                   return notify_fail("你的內力不足，沒有辦法練習石廩劍法。\n");

       if( query("qi", me)<65 )
                   return notify_fail("你的體力不夠練石廩劍法。\n");

       me->receive_damage("qi", 45);
       addn("neili", -55, me);
       return 1;
}

string perform_action_file(string action)
{
        return __DIR__"shilin-jian/" + action;
}

void skill_improved(object me)
{
        int lvl;

        lvl = me->query_skill("shilin-jian", 1);
   

        if( lvl > 120 &&
            !query("can_perform/shilin-jian/luo", me) ) 
        {
                tell_object(me, WHT "你通曉了石廩劍法「" HIC "落英紛飛" WHT "」的奧秘。\n" NOR);    
                set("can_perform/shilin-jian/luo", 1, me);
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000); 
                me->improve_skill("martial-cognize", 1500000);  
        }
}

