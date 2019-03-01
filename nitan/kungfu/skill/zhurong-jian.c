#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N身法迅捷，連出兩劍，分襲$n面門和$w，正是一招「橫空出世」",
        "force"  : 70,
        "dodge"  : 20,
        "parry"  : 25,
        "attack" : 10,
        "damage" : 35,
        "lvl"    : 0,
        "damage_type" : "刺傷",
        "skill_name"  : "橫空出世"
]),
([      "action" : "$N以劍畫弧，前腳跨出，一式「風掃落葉」，橫劍砍向$n$l，",
        "force"  : 110,
        "dodge"  : 40,
        "parry"  : 40,
        "attack" : 20,
        "damage" : 45,
        "lvl"    : 25,
        "damage_type" : "砍傷",
        "skill_name"  : "風掃落葉"
]),
([     
        "action" : "$N手中$w斜出，徑直指向$n$l，正是一招「氣沖雲霄」",
        "force"  : 160,
        "dodge"  : 30,
        "parry"  : 45,
        "attack" : 30,
        "damage" : 55,
        "lvl"    : 50,
        "damage_type" : "刺傷",
        "skill_name"  : "氣沖雲霄"
]),
([      
        "action" : "$N手中$w忽地轉動，一式「引火上身」，已順勢刺向$n$l",
        "force"  : 180, 
        "dodge"  : 45,
        "parry"  : 50,
        "attack" : 35,
        "damage" : 60,
        "lvl"    : 75,
        "damage_type" : "刺傷",
        "skill_name"  : "引火上身"
]),
([      
        "action" : "$N長嘯一聲，單腳點地，忽地躍起，挺劍刺向$n$l，正是一招「雁回祝融」",
        "force"  : 240,
        "dodge"  : 80,
        "parry"  : 60,
        "attack" : 45,
        "damage" : 80,
        "lvl"    : 100,
        "damage_type" : "刺傷",
        "skill_name"  : "雁回祝融"
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
  
            if( query("max_neili", me)<800 )
                return notify_fail("你的內力不夠，沒有辦法練祝融劍法。\n");

        if ((int)me->query_skill("sword", 1) < 120)
                return notify_fail("你的基本劍法太差，沒有辦法練祝融劍法。\n");

            if (me->query_skill("sword", 1) < me->query_skill("zhurong-jian", 1))
                return notify_fail("你的基本劍法火候有限，無法領會更高深的祝融劍法。\n");

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

        level = (int) me->query_skill("zhurong-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
            object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

               if( query("neili", me)<65 )
                       return notify_fail("你的內力不足，沒有辦法練習祝融劍法。\n");

        if( query("qi", me)<65 )
                return notify_fail("你的體力不夠練祝融劍法。\n");

            me->receive_damage("qi", 55);
            addn("neili", -60, me);
            return 1;
}

string perform_action_file(string action)
{
        return __DIR__"zhurong-jian/" + action;
}

void skill_improved(object me)
{
        int lvl;

        lvl = me->query_skill("zhurong-jian", 1);
   

        if( lvl > 160 &&
            !query("can_perform/zhurong-jian/wan", me) ) 
        {
                tell_object(me, WHT "你通曉了祝融劍法「" HIC "萬劍焚雲" WHT "」的奧秘。\n" NOR);    
                set("can_perform/zhurong-jian/wan", 1, me);
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000); 
                me->improve_skill("martial-cognize", 1500000);  
        }
}

