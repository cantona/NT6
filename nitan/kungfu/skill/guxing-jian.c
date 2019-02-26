#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" :  "$N手中$w快速猛刺，連連逼迫向$n",
        "force"  :  80,
        "dodge"  :  28,
        "damage" :  20,
        "lvl"    :  0,
        "damage_type":  "刺傷",
]),
([      "action" :  "$N手中$w橫向一掃，一式「神龍擺尾」，劍光閃過，剎那間$w已到$n$l",
        "force"  :  90,
        "dodge"  :  24,
        "damage" :  25,
        "lvl"    :  30,
        "damage_type":  "砍傷",
]),
([     
        "action" :  "劍光不定，$N忽地反轉劍身，一式「曇花一現」，猛然間$w刺向$n$l",
        "force"  :  100,
        "dodge"  :  24,
        "damage" :  30,
        "lvl"    :  60,
        "damage_type":  "刺傷",
]),
([      
        "action" :  "$N不進反退，一式「逆水行舟」，$w倒握於手中，卻斜身一劍指向$n",
        "force"  :  120, 
        "dodge"  :  30,
        "damage" :  35,
        "lvl"    :  90,
        "damage_type":  "刺傷",
]),
([      
        "action" : "$N飛身躍起，手中$w一橫，一式「橫掃千軍」，力道非凡，襲向$n$l",
        "force"  :  140,
        "dodge"  :  40,
        "damage" :  40,
        "lvl"    :  120,
        "damage_type":  "刺傷",
]),
});

int valid_learn(object me)
{
            object ob; 

            if( !(ob=query_temp("weapon", me) )
            || query("skill_type", ob) != "sword" )
                return notify_fail("你必須先找一把劍才能練劍法。\n");

            if( query("max_neili", me)<400 )
                return notify_fail("你目前的內力修為不夠，沒有辦法練孤星劍法。\n");

            if (me->query_skill("force") < 100)
                return notify_fail("你的內功修為不夠，沒有辦法練孤星劍法。\n");

            if (me->query_skill("sword", 1) < 80)
                return notify_fail("你的基本劍法火候太淺，沒有辦法練孤星劍法。\n");

            if (me->query_skill("sword", 1) < me->query_skill("guxing-jian", 1))
                return notify_fail("你的基本劍法火候有限，無法領會更高深的孤星劍法。\n");

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

        level = (int) me->query_skill("guxing-jian", 1);
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
                       return notify_fail("你的內力不足，沒有辦法練習孤星劍法。\n");

        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠練孤星劍法。\n");

        me->receive_damage("qi", 45);
        addn("neili", -35, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"guxing-jian/" + action;
}
