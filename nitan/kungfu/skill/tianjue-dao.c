#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" :  "$N手中$w忽地斜砍，嗡嗡作響，一式「天刀式」，襲向$n$l",
        "force"  :  20,
        "dodge"  :  28,
        "damage" :  15,
        "lvl"    :  0,
        "damage_type":  "砍傷",
        "skill_name"  : "天刀式",
]),
([      "action" :  "$N手中$w反轉，踏步向前，一式「風刀式」，砍向$n$l",
        "force"  :  40,
        "dodge"  :  24,
        "damage" :  20,
        "lvl"    :  25,
        "damage_type":  "砍傷",
        "skill_name"  : "風刀式",
]),
([     
        "action" :  "$N怒喝一聲，飛身躍起，一式「滅刀式」，$w嗡嗡兩聲，已到$n$l",
        "force"  :  60,
        "dodge"  :  24,
        "damage" :  18,
        "lvl"    :  50,
        "damage_type":  "砍傷",
        "skill_name"  : "滅刀式",
]),
([      
        "action" :  "$N手中$w坐砍右劈，一式「平刀式」，平平揮向$n",
        "force"  :  80, 
        "dodge"  :  30,
        "damage" :  25,
        "lvl"    :  75,
        "damage_type":  "砍傷",
        "skill_name"  : "平刀式",
]),
([      
        "action" : "$N將$w橫于胸前，猛地劈出，一式「絕刀式」，砍向$n$l",
        "force"  :  100,
        "dodge"  :  38,
        "damage" :  35,
        "lvl"    :  100,
        "damage_type":  "砍傷",
        "skill_name"  : "絕刀式",
]),
});

int valid_learn(object me)
{
            object ob; 

            if( !(ob=query_temp("weapon", me) )
            || query("skill_type", ob) != "blade" )
                return notify_fail("你必須先找一把刀才能練天絕刀法。\n");

            if( query("max_neili", me)<100 )
                return notify_fail("你目前的內力修為不夠，沒有辦法練天絕刀法。\n");

            if (me->query_skill("blade", 1) < 15)
                return notify_fail("你的基本刀法火候太淺，沒有辦法練天絕刀法。\n");

            if (me->query_skill("blade", 1) < me->query_skill("tianjue-dao", 1))
                return notify_fail("你的基本刀法火候有限，無法領會更高深的天絕刀法。\n");

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

        level = (int) me->query_skill("tianjue-dao", 1);
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
                       return notify_fail("你的內力不足，沒有辦法練天絕刀法。\n");

        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠練天絕刀法。\n");

        me->receive_damage("qi", 45);
        addn("neili", -30, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tianjue-dao/" + action;
}
