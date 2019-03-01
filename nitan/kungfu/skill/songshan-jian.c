#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" :  "$N手中$w忽地斜刺，嗡嗡作響，直指$n$l",
        "force"  :  45,
        "dodge"  :  28,
        "damage" :  5,
        "lvl"    :  0,
        "damage_type":  "刺傷",
]),
([      "action" :  "$N手中$w反轉，踏步向前，一劍刺向$n$l",
        "force"  :  60,
        "dodge"  :  24,
        "damage" :  8,
        "lvl"    :  30,
        "damage_type":  "刺傷",
]),
([     
        "action" :  "寒光閃過，$N怒喝一聲，飛身躍起，$w嗡嗡兩聲，已到$n$l",
        "force"  :  80,
        "dodge"  :  24,
        "damage" :  15,
        "lvl"    :  60,
        "damage_type":  "刺傷",
]),
([      
        "action" :  "$N手中$w化出一道弧線，緊接着劍勢收回，卻平平一劍刺向$n$l",
        "force"  :  100, 
        "dodge"  :  30,
        "damage" :  25,
        "lvl"    :  80,
        "damage_type":  "刺傷",
]),
([      
        "action" : "$N不慌不忙，猛地手中$w連續刺出，快如閃電，直指$n$l",
        "force"  :  110,
        "dodge"  :  38,
        "damage" :  30,
        "lvl"    :  100,
        "damage_type":  "刺傷",
]),
});

int valid_learn(object me)
{
            object ob; 

            if( !(ob=query_temp("weapon", me) )
            || query("skill_type", ob) != "sword" )
                return notify_fail("你必須先找一把劍才能練劍法。\n");

            if( query("max_neili", me)<100 )
                return notify_fail("你目前的內力修為不夠，沒有辦法練嵩山劍法。\n");

            if (me->query_skill("sword", 1) < 15)
                return notify_fail("你的基本劍法火候太淺，沒有辦法練嵩山劍法。\n");

            if (me->query_skill("sword", 1) < me->query_skill("songshan-jian", 1))
                return notify_fail("你的基本劍法火候有限，無法領會更高深的絕情劍法。\n");

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

        level = (int) me->query_skill("songshan-jian", 1);
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

        if( query("neili", me)<40 )
                       return notify_fail("你的內力不足，沒有辦法練習嵩山劍法。\n");

        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠練嵩山劍法。\n");

        me->receive_damage("qi", 45);
        addn("neili", -30, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"songshan-jian/" + action;
}
