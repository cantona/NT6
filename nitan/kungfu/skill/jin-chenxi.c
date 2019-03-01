// huntian-baojian.c 渾天寶鑒 金晨曦
// modified by Vin 2000

#include <ansi.h>

inherit FORCE;

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("jin-chenxi", 1);
        return lvl * lvl * 15 * 20 / 100 / 200;
}

int valid_force(string force)
{
        return 1;
}

mapping *action = ({
([  "action" : "$N施展" HIY "金晨曦" NOR "心法之「" HIY "金烏融雪" NOR "」，"
               "一拳擊到$n面門，陡然便爪，幻出一道金光射向$n$l",
    "dodge"  : -29,
    "attack" : 51,
    "parry"  : 4,
    "force"  : 284,
    "damage" : 58,
    "lvl"    : 0,
    "weapon" : HIY "金晨曦氣勁" NOR,
    "damage_type": "抓傷"
]),
([  "action" : "$N陡然使出" HIY "金晨曦" NOR "之「" HIY "十陽歸一" NOR "」，雙掌"
               "連環使出，舖天蓋地的攻向$n",
    "dodge"  : -21,
    "attack" : 93,
    "parry"  : 13,
    "force"  : 303,
    "damage" : 161,
    "lvl"    : 150,
    "weapon" : HIY "金晨曦氣勁" NOR,
    "damage_type": "內傷"
]),
([  "action" : "$N施出一招" HIY "金晨曦" NOR "之「" HIY "金陽破嶺" NOR "」，雙手"
               "作錐，攜帶著無比凌厲的內勁猛然貫出，直鑽$n的$l",
    "dodge"  : -12,
    "attack" : 98,
    "parry"  : 54,
    "force"  : 384,
    "damage" : 233,
    "lvl"    : 200,
    "weapon" : HIY "金晨曦氣勁" NOR,
    "damage_type": "刺傷"
]),
});

//string main_skill() { return "huntian-baojian"; }

int valid_enable(string usage) { return usage=="unarmed" ||  usage=="parry" ||  usage=="force"; }  

int valid_learn(object me)
{
        if (me->query_skill("huntian-baojian", 1) > 0)
                return notify_fail("你已經將渾天寶鑒神功合一，不必再單獨學習。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("修行" HIY "金晨曦" NOR "心法必須空手。\n");

        if( query("con", me)<35 )
                return notify_fail("你身子骨太弱，無法練習渾天寶鑒神功。\n");

        if ((int)me->query_skill("unarmed", 1) < 220)
                return notify_fail("你的拳腳火候無法學習" HIY "金晨曦" NOR "心法。\n");

        if ((int)me->query_skill("force", 1) < 220)
                return notify_fail("你的內功火候無法學習" HIY "金晨曦" NOR "心法。\n");

        if( query("max_neili", me)<6000 )
                return notify_fail("你的內力修為太差，無法學習" HIY "金晨曦" NOR "心法。\n");

        if ((int)me->query_skill("dian-canghai", 1) - 10 < (int)me->query_skill("jin-chenxi", 1))
                return notify_fail("你必須先提高你的" HIB "靛滄海" NOR "心法。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
    return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        return notify_fail( HIY "金晨曦" NOR "心法只能通過閱讀" HIY "金晨曦天晶" NOR "來提高。\n");
}


string perform_action_file(string action)
{
        return __DIR__"jin-chenxi/perform/" + action;
}
string exert_function_file(string action)
{
        return __DIR__"jin-chenxi/exert/" + action;
}