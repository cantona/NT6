#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "在呼呼風聲中，$N使一招「上步劈坤勢」，雙手如鉤如戢，插向$n的$l",
        "force" : 100,
        "attack": 28,
        "dodge" : 17,
        "parry" : 0,
        "damage": 13,
        "lvl"   : 0,
        "skill_name" : "上步劈坤勢" ,
        "damage_type" : "抓傷"
]),
([      "action": "$N身形一躍，費神撲上，使出一招「陰陽勁」，右手直直抓向$n的$l",
        "force" : 130,
        "attack": 35,
        "dodge" : 20,
        "parry" : 5,
        "damage": 20,
        "lvl"   : 20,
        "skill_name" : "陰陽勁" ,
        "damage_type" : "抓傷"
]),
([      "action": "$N雙手平伸，十指微微上下抖動，一招「追雲手」打向$n的$l",    
        "force" : 160,
        "attack": 39,
        "dodge" : 32,
        "parry" : 10,
        "damage": 25,
        "lvl"   : 40,
        "skill_name" : "追雲手" ,
        "damage_type" : "抓傷"
]),
([      "action": "$N使出一招「崩山嘯海勢」，猛的沖至$n跟前，雙爪暴風驟雨般抓向$n",
        "force" : 172,
        "attack": 42,
        "dodge" : 38,
        "parry" : 19,
        "damage": 29,
        "lvl"   : 60,
        "skill_name" : "崩山嘯海勢" ,
        "damage_type" : "抓傷"
]),
([      "action": "$N雙手平提胸前，左手護住面門，一招「奔雷歸穹勢」右手推向$n的$l",
        "force" : 187,
        "attack": 45,
        "dodge" : 41,
        "parry" : 21,
        "damage": 33,
        "lvl"   : 80,
        "skill_name" : "奔雷歸穹勢" ,
        "damage_type" : "抓傷"
]),
([      "action": "$N使出「抱殘守缺勢」，低喝一聲，雙手化掌為爪，一前一後抓向$n的$l",
        "force" : 203,
        "attack": 51,
        "dodge" : 49,
        "parry" : 22,
        "damage": 36,
        "lvl"   : 100,
        "skill_name" : "抱殘守缺勢" ,
        "damage_type" : "抓傷"
]),
([      "action": "$N右腿斜插$n二腿之間，一招「紫電穿雲勢」，上手取目，下手反勾$n的襠部",
        "force" : 245,
        "attack": 56,
        "dodge" : 53,
        "parry" : 27,
        "damage": 41,
        "lvl"   : 140,
        "skill_name" : "紫電穿雲勢" ,
        "damage_type" : "抓傷"
]),
([      "action": "$N使出「破岳疾勁勢」，雙爪如狂風驟雨般對準$n的$l連續抓出",
        "force" : 270,
        "attack": 61,
        "dodge" : 58,
        "parry" : 38,
        "damage": 45,
        "lvl"   : 180,
        "skill_name" : "破岳疾勁勢" ,
        "damage_type" : "抓傷"
])
});

int valid_enable(string usage) { return usage == "claw" ||  usage == "parry"; }

int valid_combine(string combo) { return combo == "zhenyu-quan"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練破岳神爪必須空手。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功火候不夠，無法學破岳神爪。\n");

        if( query("max_neili", me)<300 )
                return notify_fail("你的內力太弱，無法練破岳神爪。\n");

        if ((int)me->query_skill("claw", 1) < 20)
                return notify_fail("你的基本爪法等級太低，無法學破岳神爪。\n");

        if ((int)me->query_skill("claw", 1) < (int)me->query_skill("poyue-zhao", 1))
                return notify_fail("你的基本爪法火候水平有限，無法領會更高深的破岳神爪。\n");

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
        level = (int) me->query_skill("poyue-zhao",1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];

}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || 
            query_temp("secondary_weapon", me) )
                return notify_fail("破岳神爪必須空手練習！\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練破岳神爪。\n");

        me->receive_damage("qi", 60);
        addn("neili", -69, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"poyue-zhao/" + action;
}