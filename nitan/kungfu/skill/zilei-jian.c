#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N手中$w一轉，回身一劍，刺向$n$l，正是一招「萬紫千紅」",
        "force"  : 90,
        "dodge"  : 21,
        "parry"  : 25,
        "attack" : 10,
        "damage" : 22,
        "lvl"    : 0,
        "damage_type" : "刺傷",
        "skill_name"  : "萬紫千紅",
]),
([      "action" :  "只見$N身法陡然加快，施展出「風雨交加」，劍風盪漾，$w瞬間已至$n$l",
        "force"  : 100,
        "dodge"  : 24,
        "parry"  : 28,
        "attack" : 12,
        "damage" : 25,
        "lvl"    : 25,
        "damage_type" : "刺傷",
        "skill_name"  : "風雨交加",
]),
([      "action" : "$N縱身躍起，使出一招「晴空萬里」，陡見$w從半空直指$N$l",
        "force"  : 120,
        "dodge"  : 25,
        "parry"  : 31,
        "attack" : 13,
        "damage" : 38,
        "lvl"    : 50,
        "damage_type" : "刺傷",
        "skill_name"  : "晴空萬里",
]),
([      "action" : "$N騰空而起，一招「狂風暴雨」來勢又準又快，手中$w已到$n$l",
        "force"  : 140, 
        "dodge"  : 25,
        "parry"  : 35,
        "attack" : 15,
        "damage" : 50,
        "lvl"    : 75,
        "damage_type" : "刺傷",
        "skill_name"  : "狂風暴雨",
]),
([      "action" : "$N劍峯忽轉，一劍筆直地向$n$l刺來，內勁十足，正是一招「雨過天晴」",
        "force"  : 160,
        "dodge"  : 27,
        "parry"  : 38,
        "attack" : 18,
        "damage" : 63,
        "lvl"    : 100,
        "damage_type" : "刺傷",
        "skill_name"  : "雨過天晴",
]),
([      "action" : "$N手中$w猛然回撤，緊接着一劍，氣勢磅礴，劍氣縱橫，正是「電閃雷鳴」",
        "force"  : 180,
        "dodge"  : 30,
        "parry"  : 40,
        "attack" : 20,
        "damage" : 80,
        "lvl"    : 120,
        "damage_type" : "刺傷",
        "skill_name"  : "電閃雷鳴",
]),
});

int valid_learn(object me)
{
        object ob;

        if( !(ob=query_temp("weapon", me) )
            || query("skill_type", ob) != "sword" )
                return notify_fail("你必須先找一把劍才能練劍法。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的內力修為不夠，無法學習紫雷劍法。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候太淺，無法學習紫雷劍法。\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本劍法火候不夠，無法學習紫雷劍法。\n");

        if (me->query_skill("sword", 1) < me->query_skill("zilei-jian", 1))
                return notify_fail("你的基本劍法火候有限，無法領會更高深的紫雷劍法。\n");

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

        level = (int) me->query_skill("zilei-jian", 1);
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
                   return notify_fail("你的內力不足，沒有辦法練習紫雷劍法。\n");

       if( query("qi", me)<65 )
                   return notify_fail("你的體力不夠練紫雷劍法。\n");

       me->receive_damage("qi", 40);
       addn("neili", -50, me);
       return 1;
}

string perform_action_file(string action)
{
        return __DIR__"zilei-jian/" + action;
}
