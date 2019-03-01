// huntian-baojian.c 渾天寶鑒 靛滄海
// modified by Vin 2000

#include <ansi.h>

inherit FORCE;

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("dian-canghai", 1);
        return lvl * lvl * 15 * 18 / 100 / 200;
}

int valid_force(string force)
{
        return 1;
}

mapping *action = ({
([  "action" : "$N施出一招" HIB "靛滄海" NOR "之「" HIB "浪濤勢" NOR "」，一"
               "拳猛然攻出，氣勢恢弘，氣流澎湃，直打$n的$l",
    "dodge"  : -37,
    "attack" : 61,
    "parry"  : 14,
    "force"  : 381,
    "damage" : 31,
    "lvl"    : 0,
    "weapon" : HIB "靛滄海氣勁" NOR,
    "damage_type": "瘀傷"
]),
([  "action" : "$N錯步上前，一招" HIB "靛滄海" NOR "之「" HIB "深淵勢" NOR
               "」，雙掌猛然卷一股滔天寒流，席卷$n全身",
    "dodge"  : -38,
    "attack" : 80,
    "parry"  : 21,
    "force"  : 485,
    "damage" : 137,
    "lvl"    : 150,
    "weapon" : HIB "靛滄海氣勁" NOR,
    "damage_type": "割傷"
]),
([  "action" : "$N陡然使出" HIB "靛滄海" NOR "「" HIB "鯨吞勢" NOR "」，雙掌"
               "上下交錯，繽紛貫出，舖天掌影頓時籠罩$n",
    "dodge"  : -21,
    "attack" : 93,
    "parry"  : 13,
    "force"  : 451,
    "damage" : 141,
    "lvl"    : 150,
    "weapon" : HIB "靛滄海氣勁" NOR,
    "damage_type": "割傷"
]),
([  "action" : "$N一聲巨喝，貫出" HIB "靛滄海" NOR "心法之「" HIB "滔天勢" NOR
               "」，雙掌掀起翻天巨浪，一股凜冽寒流從九天而降，籠罩$n",
    "dodge"  : -21,
    "attack" : 93,
    "parry"  : 13,
    "force"  : 451,
    "damage" : 141,
    "lvl"    : 200,
    "weapon" : HIB "靛滄海氣勁" NOR,
    "damage_type": "割傷"
]),
});

//string main_skill() { return "huntian-baojian"; }

int valid_enable(string usage) { return usage=="unarmed" ||  usage=="parry" ||  usage=="force"; }  

int valid_learn(object me)
{
        if (me->query_skill("huntian-baojian", 1) > 0)
                return notify_fail("你已經將渾天寶鑒神功合一，不必再單獨學習。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("修行" HIB "靛滄海" NOR "心法必須空手。\n");

        if( query("con", me)<35 )
                return notify_fail("你身子骨太弱，無法練習渾天寶鑒神功。\n");

        if ((int)me->query_skill("unarmed", 1) < 200)
                return notify_fail("你的拳腳火候無法學習" HIB "靛滄海" NOR "心法。\n");

        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("你的內功火候無法學習" HIB "靛滄海" NOR "心法。\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的內力修為太差，無法學習" HIB "靛滄海" NOR "心法。\n");

        if ((int)me->query_skill("xuan-huntun", 1) - 10 < (int)me->query_skill("dian-canghai", 1))
                return notify_fail("你必須先提高你的" WHT "玄餛飩" NOR "心法。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
    return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        return notify_fail( HIB "靛滄海" NOR "心法只能通過閱讀" HIB "靛滄海天晶" NOR "來提高。\n");
}


string perform_action_file(string action)
{
        return __DIR__"dian-canghai/perform/" + action;
}
string exert_function_file(string action)
{
        return __DIR__"dian-canghai/exert/" + action;
}