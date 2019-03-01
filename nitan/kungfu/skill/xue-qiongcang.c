// huntian-baojian.c 渾天寶鑒 血穹蒼
// modified by Vin 2000

#include <ansi.h>

inherit FORCE;

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("xue-qiongcang", 1);
        return lvl * lvl * 15 * 20 / 100 / 200;
}

int valid_force(string force)
{
        return 1;
}

mapping *action = ({
([  "action" : "$N施展" HIR "血穹蒼" NOR "心法之「" HIR "血霧迷蹤" NOR "」，"
               "頓時浮現出一層血氣，身法變換無定，全身化作一道血光攻向$n",
    "dodge"  : 41,
    "attack" : 21,
    "parry"  : 9,
    "force"  : 261,
    "damage" : 33,
    "lvl"    : 0,
    "weapon" : HIR "血穹蒼氣勁" NOR,
    "damage_type": "震傷"
]),
([  "action" : "$N陡然使出" HIR "血穹蒼" NOR "之「" HIR "蒼穹無崖" NOR "」，雙掌"
               "高舉過頂，一聲悶喝，千萬掌鋒澎湃湧出，舖天蓋地席卷$n",
    "dodge"  : -61,
    "attack" : 103,
    "parry"  : -41,
    "force"  : 373,
    "damage" : 191,
    "lvl"    : 150,
    "weapon" : HIR "血穹蒼氣勁" NOR,
    "damage_type": "割傷"
]),
([  "action" : "$N施出一招" HIR "血穹蒼" NOR "之「" HIR "血陽撕天" NOR "」，凌空"
               "飛躍，雙爪攜著天穹之勁幻出兩道血光襲出，直攻$n$l",
    "dodge"  : -72,
    "attack" : 139,
    "parry"  : -54,
    "force"  : 424,
    "damage" : 253,
    "lvl"    : 200,
    "weapon" : HIR "血穹蒼氣勁" NOR,
    "damage_type": "刺傷"
]),
([  "action" : "$N站立不動，一聲暴喝，施出" HIR "血穹蒼" NOR "之「" HIR "蒼穹無悔"
               NOR "」，頓時滔天血浪至九天而降，血氣頓時籠罩$n的四面八方",
    "dodge"  : -67,
    "attack" : 198,
    "parry"  : -54,
    "force"  : 484,
    "damage" : 239,
    "lvl"    : 200,
    "weapon" : HIR "血穹蒼氣勁" NOR,
    "damage_type": "內傷"
]),
});

//string main_skill() { return "huntian-baojian"; }

int valid_enable(string usage) { return usage=="unarmed" ||  usage=="parry" ||  usage=="force"; }  

int valid_learn(object me)
{
        if (me->query_skill("huntian-baojian", 1) > 0)
                return notify_fail("你已經將渾天寶鑒神功合一，不必再單獨學習。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("修行" HIR "血穹蒼" NOR "心法必須空手。\n");

        if( query("con", me)<35 )
                return notify_fail("你身子骨太弱，無法練習渾天寶鑒神功。\n");

        if ((int)me->query_skill("unarmed", 1) < 240)
                return notify_fail("你的拳腳火候無法學習" HIR "血穹蒼" NOR "心法。\n");

        if ((int)me->query_skill("force", 1) < 240)
                return notify_fail("你的內功火候無法學習" HIR "血穹蒼" NOR "心法。\n");

        if( query("max_neili", me)<7000 )
                return notify_fail("你的內力修為太差，無法學習" HIR "血穹蒼" NOR "心法。\n");

        if ((int)me->query_skill("jin-chenxi", 1) - 10 < (int)me->query_skill("xue-qiongcang", 1))
                return notify_fail("你必須先提高你的" HIY "金晨曦" NOR "心法。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
    return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        return notify_fail( HIR "血穹蒼" NOR "心法只能通過閱讀" HIR "血穹蒼" NOR "天晶" NOR "來提高。\n");
}


string perform_action_file(string action)
{
        return __DIR__"xue-qiongcang/perform/" + action;
}
string exert_function_file(string action)
{
        return __DIR__"xue-qiongcang/exert/" + action;
}