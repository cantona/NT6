// lansha-shou.c 藍砂手 藥王谷
// Edit By Vin On 26/2/2001

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N跨前一步，雙掌陡然攻出，帶著絲絲陰風擊向$n的$l",
        "force" : 100,
        "attack": 25,
        "dodge" : 15,
        "parry" : 20,
        "damage": 10,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N左掌護胸，右掌掌心帶著極寒之氣拍向$n的$l",
        "force" : 130,
        "attack": 30,
        "dodge" : 10,
        "parry" : 15,
        "damage": 20,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N雙掌拍出滿天陰風，忽然右掌悄無聲息的拍向$n的$l",
        "force" : 180,
        "attack": 50,
        "dodge" : 20,
        "parry" : 30,
        "damage": 30,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N怪叫一聲，身形一躍，左掌快若疾電般擊向$n的$l",
        "force" : 210,
        "attack": 65,
        "dodge" : 25,
        "parry" : 20,
        "damage": 35,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N陰笑一聲，雙掌一錯，右掌忽然暴長數尺擊向$n的$l",
        "force" : 210,
        "attack": 65,
        "dodge" : 25,
        "parry" : 20,
        "damage": 35,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N身形急晃，一躍而至$n跟前，右掌帶著沖天寒氣擊向$n的$l",
        "force" : 210,
        "attack": 65,
        "dodge" : 25,
        "parry" : 20,
        "damage": 35,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N仰天長嘯，雙掌掌風似千古不化的寒冰般撲向$n的$l",
        "force" : 210,
        "attack": 65,
        "dodge" : 25,
        "parry" : 20,
        "damage": 35,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N身法陡然一變，掌影千變萬幻，令$n無法躲閃",
        "force" : 250,
        "attack": 45,
        "dodge" : 15,
        "parry" : 20,
        "damage": 25,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N仰天一聲狂嘯，雙掌攜帶著萬古冰堅直直貫向$n",
        "force" : 330,
        "attack": 35,
        "dodge" : 25,
        "parry" : 20,
        "damage": 15,
        "damage_type" : "瘀傷"
])
});

int valid_enable(string usage) { return usage == "hand" || usage == "parry"; }

int valid_combine(string combo) { return combo == "dusha-zhang"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練藍砂手必須空手。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，無法練習藍砂手。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的內力太弱，無法練習藍砂手。\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("lansha-shou", 1))
                return notify_fail("你的基本手法水平有限，無法領會更高深的藍砂手。\n");

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
        level   = (int) me->query_skill("lansha-shou",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練藍砂手。\n");

        me->receive_damage("qi", 40);
        addn("neili", -60, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("lansha-shou", 1);
        flvl=query("jiali", me);
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
           victim->affect_by("sha_poison",
                ([ "level" : flvl + random(flvl),
                   "id":query("id", me),
                   "duration" : lvl / 50 + random(lvl / 20) ])))
        {
                return HIB "$n" HIB "忽然感到一股莫名的惡心，全身癱軟，嘴皮烏紫。\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"lansha-shou/" + action;
}