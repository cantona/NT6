#include <ansi.h>
inherit SKILL;

mapping *action = ({
([  "action": "$N使出一招「山陰手」，運掌如飛，招招直打$n的$l",
    "force" : 60,
    "attack": 25,
    "dodge" : 10,
    "parry" : 16,
    "damage": 15,
    "lvl"   : 0,
    "skill_name" : "山陰手" ,
    "damage_type" : "瘀傷"
]),
([  "action": "$N使出一招「千層刃」，雙掌急運內力，帶着凜冽的掌風直拍$n的$l",
    "force" : 80,
    "attack": 55,
    "dodge" : 15,
    "parry" : 19,
    "damage": 25,
    "lvl"   : 20,
    "skill_name" : "千層刃" ,
    "damage_type" : "瘀傷"
]),
([  "action": "$N慘然一聲長嘯，一招「消魂刀」，雙掌猛然擊下，直撲$n的要脈",
    "force" : 100,
    "attack": 45,
    "dodge" : 20,
    "parry" : 18,
    "damage": 50,
    "lvl"   : 40,
    "skill_name" : "消魂刀" ,
    "damage_type" : "瘀傷"
]),
([  "action": "$N骨骼暴響，雙臂忽然暴長數尺，一招「離魂掌」直直攻向$n的$l",
    "force" : 130,
    "attack": 40,
    "dodge" : 20,
    "parry" : 23,
    "damage": 65,
    "lvl"   : 80,
    "skill_name" : "離魂掌" ,
    "damage_type" : "瘀傷"
]),
([  "action": "$N施展出一招「奪魂手」，雙掌繽紛拍出，陡然間雙掌已至$n跟前",
    "force" : 150,
    "attack": 61,
    "dodge" : 32,
    "parry" : 35,
    "damage": 80,
    "lvl"   : 120,
    "skill_name" : "奪魂手" ,
    "damage_type" : "瘀傷"
]),
});

int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
            return notify_fail("練陰陽掌必須空手。\n");

        if( query("max_neili", me)<200 )
            return notify_fail("你的內力修為太淺，無法練習陰陽掌。\n");

        if ((int)me->query_skill("strike", 1) < 30)
            return notify_fail("你的基本掌法太差，無法領會陰陽掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("yinyang-zhang", 1))
            return notify_fail("你的基本掌法火候不夠，無法領會更高深的陰陽掌。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action); i > 0; i--)
                if (level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("yinyang-zhang", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<80 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠。\n");

        me->receive_damage("qi", 45);
        addn("neili", -48, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yinyang-zhang/" + action;
}
