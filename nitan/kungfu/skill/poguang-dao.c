#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N手中$w橫空而出，一式「破空式」，$w已到$n$l",
        "force"  : 90,
        "dodge"  : 21,
        "parry"  : 25,
        "attack" : 10,
        "damage" : 22,
        "lvl"    : 0,
        "damage_type" : "刺傷",
        "skill_name"  : "破空式",
]),
([      "action" : "$N手中$w平平揮出，一式「橫空式」，$w砍向$n$l ",
        "force"  : 100,
        "dodge"  : 24,
        "parry"  : 28,
        "attack" : 12,
        "damage" : 25,
        "lvl"    : 25,
        "damage_type" : "刺傷",
        "skill_name"  : "橫空式",
]),
([      "action" : "$N縱身躍起，施出一式「冷光式」，$w寒光一閃已到$n$l",
        "force"  : 120,
        "dodge"  : 25,
        "parry"  : 31,
        "attack" : 13,
        "damage" : 38,
        "lvl"    : 50,
        "damage_type" : "刺傷",
        "skill_name"  : "冷光式",
]),
([      "action" : "$N騰空而起，一式「穿陽式」，手中$w直砍向$n$l",
        "force"  : 140, 
        "dodge"  : 25,
        "parry"  : 35,
        "attack" : 15,
        "damage" : 50,
        "lvl"    : 75,
        "damage_type" : "刺傷",
        "skill_name"  : "穿陽式",
]),
([      "action" : "$N刀峰忽轉，施出一式「回旋式」，$w蜿蜒而進，襲向$n$l",
        "force"  : 160,
        "dodge"  : 27,
        "parry"  : 38,
        "attack" : 18,
        "damage" : 63,
        "lvl"    : 100,
        "damage_type" : "刺傷",
        "skill_name"  : "回旋式",
]),
([      "action" : "$N怒喝一聲，手中$w狂舞不定，一式「狂風式」，如無數把$w罩向$n",
        "force"  : 180,
        "dodge"  : 30,
        "parry"  : 40,
        "attack" : 20,
        "damage" : 80,
        "lvl"    : 120,
        "damage_type" : "刺傷",
        "skill_name"  : "狂風式",
]),
});

int valid_learn(object me)
{
        object ob;

        if( !(ob=query_temp("weapon", me) )
            || query("skill_type", ob) != "blade" )
                return notify_fail("你必須先找一把劍才能練破光刀法。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的內力修為不夠，無法學習破光刀法。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候太淺，無法學習破光刀法。\n");

        if ((int)me->query_skill("blade", 1) < 100)
                return notify_fail("你的基本刀法火候不夠，無法學習破光刀法。\n");

        if (me->query_skill("blade", 1) < me->query_skill("poguang-dao", 1))
                return notify_fail("你的基本劍法火候有限，無法領會更高深的破光刀法。\n");

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

        level = (int) me->query_skill("poguang-dao", 1);
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
                   return notify_fail("你的內力不足，沒有辦法練習破光刀法。\n");

       if( query("qi", me)<55 )
                   return notify_fail("你的體力不夠練破光刀法。\n");

       me->receive_damage("qi", 40);
       addn("neili", -50, me);

       return 1;
}

string perform_action_file(string action)
{
        return __DIR__"poguang-dao/" + action;
}
