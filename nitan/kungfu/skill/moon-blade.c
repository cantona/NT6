// This program is a part of NITAN MudLIB
// moon-blade.c

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N揮舞$w，使出一招「圓月當空」，上劈下撩，左擋右開，齊齊罩向$n",
        "skill_name" : "圓月當空",
        "force"  : 120,
        "attack" : 35,
        "dodge"  : -30,
        "parry"  : -32,
        "lvl"    : 0,
        "damage" : 240,
        "damage_type" : "割傷",
        "skill_name"  : "圓月當空",
]),
([      "action" : "$N展身虛步，提腰躍落，一招「雲遮霧擾」，刀鋒一卷，攔腰斬向$n",
        "skill_name" : "雲遮霧擾",
        "force"  : 160,
        "attack" : 42,
        "dodge"  : -40,
        "parry"  : -45,
        "lvl"    : 30,
        "damage" : 250,
        "damage_type" : "割傷",
        "skill_name"  : "雲遮霧擾",
]),
([      "action" : "$N手中$w一抖，一招「撥雲見月」，手中$w化成一道銀練，攻向$n的$l",
        "skill_name" : "撥雲見月",
        "force"  : 185,
        "attack" : 51,
        "dodge"  : -45,
        "parry"  : -47,
        "lvl"    : 50,
        "damage" : 260,
        "damage_type" : "割傷",
        "skill_name"  : "撥雲見月",
]),
([      "action" : "$N神態悠閒，手中$w觸地，一招「對影三人」從不可思議的角度劃向$n的$l",
        "skill_name" : "對影三人",
        "force"  : 220,
        "attack" : 55,
        "dodge"  : -55,
        "parry"  : -61,
        "lvl"    : 80,
        "damage" : 270,
        "damage_type" : "割傷",
        "skill_name"  : "對影三人",
]),
([      "action" : "$N手中$w手中$w不停地顫抖著，劍氣不斷的發出，這招「花前月下」齊齊罩向$n",
        "skill_name" : "花前月下",
        "force"  : 255,
        "attack" : 65,
        "dodge"  : -60,
        "parry"  : -72,
        "lvl"    : 100,
        "damage" : 280,
        "damage_type" : "割傷",
        "skill_name"  : "花前月下",
]),
([      "action" : "$N手中$w如同流星暴雨，毫不停歇地朝$n砍去，正是一招「常娥奔月」",
        "skill_name" : "常娥奔月",
        "force"  : 290,
        "attack" : 70,
        "dodge"  : -70,
        "parry"  : -75,
        "lvl"    : 120,
        "damage" : 290,
        "damage_type" : "割傷",
        "skill_name"  : "常娥奔月",
]),
([      "action" : "$N手中的$w帶起一陣狂風，頓時無數朵刀花夾帶著風雷之聲一招「刀光月影」朝$n的$l處砍去",
        "skill_name" : "刀光月影",
        "force"  : 320,
        "attack" : 80,
        "dodge"  :- 85,
        "parry"  : -85,
        "lvl"    : 140,
        "damage" : 300,
        "damage_type" : "割傷",
        "skill_name"  : "刀光月影",
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        object weapon;

        if( query("con", me)<26 )
                return notify_fail("你研究了半天，只覺得根骨有些差，始終無法理解其中的真諦。\n");

        if( query("int", me)<30 )
                return notify_fail("你研究了半天，只覺得悟性有些差，始終無法理解其中的真諦。\n");

        if( query("str", me)<26 )
                return notify_fail("你研究了半天，感覺膂力有些低，始終無法隨意施展。\n");

        if( query("dex", me)<39 )
                return notify_fail("你研究了半天，只覺依自己的身法靈動性，根本無法修習這門武功。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 500)
                return notify_fail("你的內功火候太淺。\n");

        weapon=query_temp("weapon", me);
        if (me->query_skill("moon-blade", 1) < 1000 &&
              (!objectp(weapon) || query("id", weapon) != "moon blade") )
                return notify_fail("你的圓月刀法大成之前必須有圓月彎刀配合才能學習。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("moon-blade", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        return notify_fail("圓月刀法博大精深，無法靠著普通的練習提升。\n");
        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力不夠，練不了圓月彎刀。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠，練不了圓月彎刀。\n");

        if (! present("moon blade", me) && me->query_skill("moon-blade") < 400)
                return notify_fail("你的圓月刀法大成之前必須有圓月彎刀配合才能練習。\n");

        me->receive_damage("qi", 55);
        addn("neili", -61, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage)
{
        mixed result;
        if (damage < 100) return 0;

        if (random(damage) > victim->query_str() / 10)
        {
                result = ([ "damage" : damage ]);
                result += ([ "msg" : HIW "$N" HIW "仰天一嘯，刀勁迸發，滿天具是雪亮的刀光，猶如滿月的月光般美麗，\n"
                                     "但卻讓人感到落入森羅地獄般，全身止不住的戰抖，\n"
                                     HIR "霎時一股冰寒的刀氣掠過$n" HIR "全身，$n" HIR "全身頓時鮮血淋漓，搖搖欲倒。\n" NOR ]);

                return result;
        }
}

string perform_action_file(string action)
{
        return __DIR__"moon-blade/" + action;
}
