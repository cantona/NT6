#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" :  "$N飛身躍起，挺劍刺向$n$l，正是一招「盛氣凌人」",
        "force"  :  90,
        "dodge"  :  18,
        "parry"  :  20,
        "attack" :  10,
        "damage" :  20,
        "lvl"    :  0,
        "damage_type" : "刺傷",
        "skill_name"  : "盛氣凌人"
]),
([      "action" :  "$N氣運於劍，陡然直進，一招「一劍穿心」已然使出，$w直指$n$l",
        "force"  :  120,
        "dodge"  :  25,
        "parry"  :  40,
        "attack" :  24,
        "damage" :  35,
        "lvl"    :  25,
        "damage_type" : "刺傷",
        "skill_name"  : "一劍穿心"
]),
([     
        "action" :  "$N劍勢突變，飄忽不定，一式「千變萬化」，向$n$l刺去",
        "force"  :  140,
        "dodge"  :  57,
        "parry"  :  40,
        "attack" :  30,
        "damage" :  63,
        "lvl"    :  50,
        "damage_type" : "刺傷",
        "skill_name"  : "千變萬化"
]),
([      
        "action" :  "$N輕嘯一聲，$w一抖，一式「氣冠長虹」，眨眼間$w已到$n$l",
        "force"  :  160, 
        "dodge"  :  45,
        "parry"  :  45,
        "attack" :  35,
        "damage" :  48,
        "lvl"    :  75,
        "damage_type" : "刺傷",
        "skill_name"  : "氣冠長虹"
]),
([      
        "action" : "$N踏前半步，手中$w如影如幻，竟向$n$l刺去，正是一招「壯志凌雲」",
        "force"  :  180,
        "dodge"  :  80,
        "parry"  :  60,
        "attack" :  55,
        "damage" :  60,
        "lvl"    :  100,
        "damage_type" : "刺傷",
        "skill_name"  : "壯志凌雲"
]),
});

int valid_learn(object me)
{
            object ob; 

            if( !(ob=query_temp("weapon", me) )
            || query("skill_type", ob) != "sword" )
                return notify_fail("你必須先找一把劍才能練劍法。\n");
   
        if( query("max_neili", me)<300 )
                return notify_fail("你的內力不夠，沒有辦法練凌雲劍法。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("sword", 1) < 90)
                   return notify_fail("你的基本劍法火候不夠，無法學習凌雲劍法。\n");

        if (me->query_skill("sword", 1) < me->query_skill("lingyun-jian", 1))
                return notify_fail("你的基本劍法火候有限，無法領會更高深的凌雲劍法。\n");

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

        level = (int) me->query_skill("lingyun-jian", 1);
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

       if( query("neili", me)<60 )
                   return notify_fail("你的內力不足，沒有辦法練習凌雲劍法。\n");

       if( query("qi", me)<65 )
                   return notify_fail("你的體力不夠練凌雲劍法。\n");

       me->receive_damage("qi", 50);
       addn("neili", -50, me);
       return 1;
}

string perform_action_file(string action)
{
        return __DIR__"lingyun-jian/" + action;
}