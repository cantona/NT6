// This program is a part of NITAN MudLIB
// mingyue-blade.c (天涯明月刀)

#include <ansi.h>;
inherit SKILL;

mapping *action = ({
([      "action" : "$N身形沉穩，手中$w猛的一轉，施展出單刀的刀法，一招「舉杯邀明月」朝$n的$l處砍去！",
        "force"  : 120,
        "attack" : 35,
        "dodge"  : -30,
        "parry"  : -12,
        "lvl"    : 0,
        "damage" : 240,
        "damage_type" : "割傷",
        "skill_name"  : "舉杯邀明月",
]),
([      "action" : "$N刀鋒一轉，劃過一道圓弧，突然又於其上施展出挑、刺的招數，正是一招「對影成三人」！",
        "force"  : 160,
        "attack" : 42,
        "dodge"  : -40,
        "parry"  : -15,
        "lvl"    : 40,
        "damage" : 250,
        "damage_type" : "割傷",
        "skill_name"  : "對影成三人",
]),
([      "action" : "$N刀法突然凌厲，專走險路，赫然竟是馬刀的路數，只見一招「天涯共此時」朝$n的$l砍去！",
        "force"  : 185,
        "attack" : 51,
        "dodge"  : -45,
        "parry"  : -17,
        "lvl"    : 60,
        "damage" : 260,
        "damage_type" : "割傷",
        "skill_name"  : "天涯共此時",
]),
([      "action" : "$N體內的真氣在不斷變化，不斷遊移，突然一招「海角若比鄰」斬向$n的$l!",
        "force"  : 220,
        "attack" : 55,
        "dodge"  : -55,
        "parry"  : -21,
        "lvl"    : 80,
        "damage" : 270,
        "damage_type" : "割傷",
        "skill_name"  : "海角若比鄰",
]),
});

int valid_enable(string usage){ return usage == "blade" || usage == "parry";}

int valid_learn(object me)
{
        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("blade", 1) < 140)
                return notify_fail("你的基本刀法不夠，難以修煉天涯明月刀。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("mingyue-blade", 1))
                return notify_fail("你的基本刀法水平有限，無法領會更高深的天涯明月刀。\n");

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
        level   = (int) me->query_skill("mingyue-blade", 1);
        if (random(me->query_skill("blade")) > 180
        &&  me->query_skill("force") > 200
         && query("neili", me)>1000
         && objectp(weapon=query_temp("weapon", me)) )
        {
                addn("neili", -300, me);
                return ([
                        "action": "$N使出一招" HIM "「天涯明月相思淚」" NOR "，$w霍地射出寒光點點，猶如冬夜寒雨般鋪天蓋地掃向$n",
                        "damage": 500,
                        "dodge" : -100,
                        "parry" : -150,
                        "attack": 150,
                        "damage_type": "割傷"
                ]);
        }
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的體力不夠，練不了天涯明月刀。\n");

        if( query("neili", me)<120 )
                return notify_fail("你的內力不夠，練不了天涯明月刀。\n");

        me->receive_damage("qi", 64);
        addn("neili", -84, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        object weapon;
        int lvl = me->query_skill("mingyue-blade", 1);
        weapon=query_temp("weapon", me);

        if (lvl < 180 || lvl / 2 + random(lvl) < (int)victim->query_skill("dodge", 1) ||
            query("neili", me)<500 ||
            me->query_skill("dodge", 1) < 180 ||
            me->query_skill("force", 1) < 150 ||
            victim->is_busy() )
                 return 0;

        message_vision(HIW "\n$N" HIW "右手" + weapon->name() + HIW "猛然旋轉，刀光突"
                       "現，剎那間已將$n" HIW "逼的退無可退。\n" NOR, me, victim);
        addn("neili", -80, me);
        victim->start_busy(2 + random(lvl / 60));
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"mingyue-blade/" + action;
}