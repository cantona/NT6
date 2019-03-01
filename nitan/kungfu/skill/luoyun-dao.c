#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" :  "$N手中$w平平一刀，一式「萬裡烏雲」，揮向$n$l",
        "force"  :  80,
        "dodge"  :  28,
        "damage" :  20,
        "lvl"    :  0,
        "damage_type":  "刺傷",
        "skill_name"  : "萬裡烏雲",
]),
([      "action" :  "$N手中$w自空而下，一式「雲深霧鎖」，劈向$n$l",
        "force"  :  90,
        "dodge"  :  24,
        "damage" :  25,
        "lvl"    :  30,
        "damage_type":  "砍傷",
        "skill_name"  : "雲深霧鎖",
]),
([     
        "action" :  "刀光閃爍間，$N騰空而起，半空直下，一式「五雷轟頂」"
                    "，手中$w已經到$n$l",
        "force"  :  100,
        "dodge"  :  24,
        "damage" :  30,
        "lvl"    :  60,
        "damage_type":  "刺傷",
        "skill_name"  : "五雷轟頂",
]),
([      
        "action" :  "$N不慌不忙，一式「風聲蕭蕭」，手中$w反轉不定，猛地"
                    "一刀砍向$n$l",
        "force"  :  120, 
        "dodge"  :  30,
        "damage" :  35,
        "lvl"    :  90,
        "damage_type":  "刺傷",
        "skill_name"  : "風聲蕭蕭",
]),
([      
        "action" : "$N雙手握刀，一式「力劈群山」，手中$w自上而下，如長龍"
                   "般而下，砍向$n$l",
        "force"  :  140,
        "dodge"  :  40,
        "damage" :  40,
        "lvl"    :  120,
        "damage_type":  "刺傷",
        "skill_name"  : "力劈群山",
]),
});

int valid_learn(object me)
{
            object ob; 

            if( !(ob=query_temp("weapon", me) )
            || query("skill_type", ob) != "blade" )
                return notify_fail("你必須先找一把劍才能練落雲刀法。\n");

            if( query("max_neili", me)<400 )
                return notify_fail("你目前的內力修為不夠，沒有辦法練落雲刀法。\n");

            if (me->query_skill("force") < 100)
                return notify_fail("你的內功修為不夠，沒有辦法練落雲刀法。\n");

            if (me->query_skill("blade", 1) < 80)
                return notify_fail("你的基本劍法火候太淺，沒有辦法練落雲刀法。\n");

            if (me->query_skill("blade", 1) < me->query_skill("luoyun-dao", 1))
                return notify_fail("你的基本劍法火候有限，無法領會更高深的孤星劍法。\n");

            return 1;
}

int valid_enable(string usage)
{
            return usage == "blade" || usage == "parry";
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

        level = (int) me->query_skill("luoyun-dao", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
            object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if( query("neili", me)<40 )
                       return notify_fail("你的內力不足，沒有辦法練習落雲刀法。\n");

        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠練落雲刀法。\n");

        me->receive_damage("qi", 45);
        addn("neili", -35, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"luoyun-dao/" + action;
}
