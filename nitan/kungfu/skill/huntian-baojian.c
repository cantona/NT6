#include <ansi.h>

inherit FORCE;

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("huntian-baojian", 1);
        return lvl * lvl * 15 * 50 / 100 / 200;
}

mapping *action = ({
([  "action" : "$N施出一招" HIB "靛滄海" NOR "之「" HIB "浪濤勢" NOR "」，一"
               "拳猛然攻出，氣勢恢弘，氣流澎湃，直打$n的$l",
    "dodge"  : 137,
    "attack" : 161,
    "parry"  : 114,
    "force"  : 481,
    "damage" : 131,
    "weapon" : HIB "靛滄海氣勁" NOR,
    "damage_type": "割傷"
]),
([  "action" : "$N錯步上前，一招" HIB "靛滄海" NOR "之「" HIB "深淵勢" NOR
               "」，雙掌猛然卷一股滔天寒流，席捲$n全身",
    "dodge"  : 138,
    "attack" : 180,
    "parry"  : 121,
    "force"  : 485,
    "damage" : 137,
    "weapon" : HIB "靛滄海氣勁" NOR,
    "damage_type": "割傷"
]),
([  "action" : "$N陡然使出" HIB "靛滄海" NOR "「" HIB "鯨吞勢" NOR "」，雙掌"
               "上下交錯，繽紛貫出，鋪天掌影頓時籠罩$n",
    "dodge"  : 121,
    "attack" : 193,
    "parry"  : 113,
    "force"  : 451,
    "damage" : 241,
    "weapon" : HIB "靛滄海氣勁" NOR,
    "damage_type": "割傷"
]),
([  "action" : "$N一聲巨喝，貫出" HIB "靛滄海" NOR "心法之「" HIB "滔天勢" NOR
               "」，雙掌掀起翻天巨浪，一股凜冽寒流從九天而降，籠罩$n",
    "dodge"  : 121,
    "attack" : 193,
    "parry"  : 113,
    "force"  : 451,
    "damage" : 241,
    "weapon" : HIB "靛滄海氣勁" NOR,
    "damage_type": "割傷"
]),
([  "action" : "$N施展" HIR "血穹蒼" NOR "心法之「" HIR "血霧迷蹤" NOR "」，"
               "頓時浮現出一層血氣，身法變換無定，全身化作一道血光攻向$n",
    "dodge"  : 241,
    "attack" : 221,
    "parry"  : 209,
    "force"  : 261,
    "damage" : 233,
    "weapon" : HIR "血穹蒼氣勁" NOR,
    "damage_type": "割傷"
]),
([  "action" : "$N陡然使出" HIR "血穹蒼" NOR "之「" HIR "蒼穹無崖" NOR "」，雙掌"
               "高舉過頂，一聲悶喝，千萬掌鋒澎湃湧出，鋪天蓋地席捲$n",
    "dodge"  : 261,
    "attack" : 103,
    "parry"  : 241,
    "force"  : 373,
    "damage" : 391,
    "weapon" : HIR "血穹蒼氣勁" NOR,
    "damage_type": "割傷"
]),
([  "action" : "$N施出一招" HIR "血穹蒼" NOR "之「" HIR "血陽撕天" NOR "」，凌空"
               "飛躍，雙爪攜着天穹之勁幻出兩道血光襲出，直攻$n$l",
    "dodge"  : 272,
    "attack" : 239,
    "parry"  : 254,
    "force"  : 424,
    "damage" : 353,
    "weapon" : HIR "血穹蒼氣勁" NOR,
    "damage_type": "刺傷"
]),
([  "action" : "$N站立不動，一聲暴喝，施出" HIR "血穹蒼" NOR "之「" HIR "蒼穹無悔"
               NOR "」，頓時滔天血浪至九天而降，血氣頓時籠罩$n的四面八方",
    "dodge"  : 267,
    "attack" : 298,
    "parry"  : 254,
    "force"  : 484,
    "damage" : 339,
    "weapon" : HIR "血穹蒼氣勁" NOR,
    "damage_type": "刺傷"
]),
([  "action" : "$N施展" HIY "金晨曦" NOR "心法之「" HIY "金烏融雪" NOR "」，"
               "一拳擊到$n面門，陡然便爪，幻出一道金光射向$n$l",
    "dodge"  : 329,
    "attack" : 251,
    "parry"  : 304,
    "force"  : 884,
    "damage" : 358,
    "weapon" : HIY "金晨曦氣勁" NOR,
    "damage_type": "刺傷"
]),
([  "action" : "$N陡然使出" HIY "金晨曦" NOR "之「" HIY "十陽歸一" NOR "」，雙掌"
               "連環使出，鋪天蓋地的攻向$n",
    "dodge"  : 321,
    "attack" : 393,
    "parry"  : 513,
    "force"  : 703,
    "damage" : 461,
    "weapon" : HIY "金晨曦氣勁" NOR,
    "damage_type": "刺傷"
]),
([  "action" : "$N施出一招" HIY "金晨曦" NOR "之「" HIY "金陽破嶺" NOR "」，雙手"
               "作錐，攜帶着無比凌厲的內勁猛然貫出，直鑽$n的$l",
    "dodge"  : 312,
    "attack" : 398,
    "parry"  : 454,
    "force"  : 884,
    "damage" : 433,
    "weapon" : HIY "金晨曦氣勁" NOR,
    "damage_type": "刺傷"
]),
});

int valid_enable(string usage)
{
        return usage == "force" || usage == "unarmed" || usage == "parry";
}

int valid_force(string force) { return 1; }

int double_attack() { return 1; }

mapping query_action(object me)
{
        return action[random(sizeof(action))];
}

int valid_learn(object me)
{
        return notify_fail("%……—（%￥·！·！·*#—\n");
}

int practice_skill(object me)
{
        return notify_fail("%……—（%￥·！·！·*#—\n");
}

int difficult_level()
{
        return 9000;
}

string perform_action_file(string action)
{
        return __DIR__"huntian-baojian/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"huntian-baojian/exert/" + action;
}