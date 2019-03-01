#include <ansi.h>;
inherit SKILL;

mapping *action = ({
([      "action" : "$N左手單臂掄起$w，一招「開山」，夾雜著陣陣風聲向$n$l砸去",
        "skill_name" : "開山",
        "force" : 320,
        "attack": 27,
        "dodge" : -30,
        "parry" : -34,
        "lvl"   : 0,
        "damage": 62,
        "damage_type" : "挫傷",
]),
([      "action" : "$N將手中$w劃出一道半弧，一式「斷岳」便如流星墜地，直轟$n",
        "skill_name" : "斷岳",
        "force" : 460,
        "attack": 38,
        "dodge" : -27,
        "parry" : -45,
        "lvl"   : 40,
        "damage": 66,
        "damage_type" : "挫傷",
]),
([      "action" : "突然間$N手中$w挾著無上勁力，一招「劈天」施出，飛砍向$n而去",
        "skill_name" : "劈天",
        "force" : 500,
        "attack": 43,
        "dodge" : -25,
        "parry" : -47,
        "lvl"   : 80,
        "damage": 70,
        "damage_type" : "挫傷",
]),
([      "action" : "$N嗔目大喝，施一招「分海」，$w在勁力推動之下，向$n緩緩壓來",
        "skill_name" : "分海",
        "force" : 540,
        "attack": 51,
        "dodge" : -45,
        "parry" : -50,
        "lvl"   : 120,
        "damage": 75,
        "damage_type" : "挫傷",
]),
([      "action" : "$N緊握$w，那勢「還虛」的勁力便如同排山倒海般朝$n飛旋而出",
        "skill_name" : "還虛",
        "force" : 580,
        "attack": 55,
        "dodge" : -20,
        "parry" : -25,
        "lvl"   : 160,
        "damage": 80,
        "damage_type" : "挫傷",
]),
([      "action" : "$N高舉$w，那勢「破衲」的勁力便如同排山倒海般朝$n飛旋而出",
        "skill_name" : "破衲",
        "force" : 620,
        "attack": 65,
        "dodge" : -40,
        "parry" : -35,
        "lvl"   : 180,
        "damage": 98,
        "damage_type" : "挫傷",
]),
([      "action" : "$N反轉$w，那勢「克己」的勁力便如同排山倒海般朝$n飛旋而出",
        "skill_name" : "克己",
        "force" : 640,
        "attack": 69,
        "dodge" : -62,
        "parry" : -33,
        "lvl"   : 200,
        "damage": 104,
        "damage_type" : "挫傷",
]),
});


int valid_enable(string usage) { return usage == "hammer" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("str", me)<32 )
                return notify_fail("你的先天膂力孱弱，無法修煉盤古七勢。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力修為太淺，無法修煉盤古七勢。\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("你的內功火候太淺，無法修煉盤古七勢。\n");

        if ((int)me->query_skill("hammer", 1) < 80)
                return notify_fail("你的基本錘法火候太淺，無法修煉盤古七勢。\n");

        if ((int)me->query_skill("hammer", 1) < (int)me->query_skill("pangu-qishi", 1))
                return notify_fail("你的基本錘法水平有限，無法領會更高深的盤古七勢。\n");

        return 1;
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
        level = (int) me->query_skill("pangu-qishi",1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "hammer" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<100 )
                return notify_fail("你的體力不夠，練不了盤古七勢。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠，練不了盤古七勢。\n");

        me->receive_damage("qi", 90);
        addn("neili", -90, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"pangu-qishi/" + action;
}