#include <ansi.h>;
inherit SKILL;

mapping *action = ({
([      "action" : "$N一招「秋風起夕」，右手立掌而出，左手單臂掄起$w，夾雜著陣陣風聲向$n$l砸去",
        "skill_name" : "秋風起夕",
        "force" : 320,
        "attack": 27,
        "dodge" : -10,
        "parry" : 40,
        "lvl"   : 0,
        "damage": 62,
        "damage_type" : "挫傷",
]),
([      "action" : "$N將手中$w拋上半空，躍起一掌砸在$w上，這式「風吹雲散」有如流星墜地，直轟$n",
        "skill_name" : "風吹雲散",
        "force" : 260,
        "attack": 38,
        "dodge" : -20,
        "parry" : 45,
        "lvl"   : 40,
        "damage": 66,
        "damage_type" : "挫傷",
]),
([      "action" : "憑空閃出一道雪白的光幕，光電閃爍中$w挾「雷雨交加」的無上勁力，從$N手中飛出砍向$n的$l",
        "skill_name" : "雷雨交加",
        "force" : 300,
        "attack": 43,
        "dodge" : -20,
        "parry" : 47,
        "lvl"   : 80,
        "damage": 70,
        "damage_type" : "挫傷",
]),
([      "action" : "$N雙眼磕閉，全身衣物卻在內勁沖擊下漲如氣球，那$w在這「八方雲湧」的推動下，向$n緩緩壓來",
        "skill_name" : "八方雲湧",
        "force" : 340,
        "attack": 51,
        "dodge" : 5,
        "parry" : 50,
        "lvl"   : 120,
        "damage": 75,
        "damage_type" : "挫傷",
]),
([      "action" : "$N雙手畫圈，光幕宛如一輪明月，將$P籠罩，這「九天雷動」的勁力帶著$w以排山倒海之勢飛旋而出",
        "skill_name" : "九天雷動",
        "force" : 380,
        "attack": 55,
        "dodge" : -10,
        "parry" : 55,
        "lvl"   : 160,
        "damage": 80,
        "damage_type" : "挫傷",
]),
});


int valid_enable(string usage) { return usage == "hammer" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<800 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("hammer", 1) < (int)me->query_skill("fenglei-panfa", 1))
                return notify_fail("你的基本錘法水平有限，無法領會更高深的風雷盤法。\n");

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
        level = (int) me->query_skill("fenglei-panfa",1);
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
                return notify_fail("你的體力不夠，練不了風雷盤法。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠，練不了風雷盤法。\n");

        me->receive_damage("qi", 90);
        addn("neili", -90, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"fenglei-panfa/" + action;
}