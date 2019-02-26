// zijin-chuifa.c 紫金錘法

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$N雙手一震，手中$w夾帶着悶雷般的響聲，劈頭蓋臉地就向$n砸了過去。",
        "force"  : 100,
        "dodge"  : -3,
        "parry"  : 15,
        "damage" : 20,
        "lvl"    : 0,
        "damage_type": "挫傷"
]),
([      "action" : "只見$N眼冒兇光，青筋凸起，抄起$w就朝$n的$l狠命掃去。",
        "force"  : 150,
        "dodge"  : -5,
        "parry"  : 20,
        "damage" : 30,
        "lvl"    : 20,
        "damage_type": "瘀傷"
]),
([      "action" : "$N手中的$w舉重若輕，勢若瘋虎地向$n$l連連砸去。",
        "force"  : 180,
        "dodge"  : -8,
        "parry"  : 20,
        "damage" : 40,
        "lvl"    : 50,
        "damage_type": "瘀傷"
]),
([      "action" : "$N全然不顧$n的招式，舉起$w朝着$n當頭就是一錘。",
        "force"  : 210,
        "dodge"  : -12,
        "parry"  : 30,
        "damage" : 50,
        "lvl"    : 80,
        "damage_type": "挫傷"
]),
([      "action" : "$N將$w高舉過肩，蓄緊力發，對準$n的$l發出雷霆一擊。",
        "force"  : 250,
        "dodge"  : -15,
        "parry"  : 35,
        "damage" : 60,
        "lvl"    : 100,
        "damage_type": "瘀傷"
]),
});

int valid_learn(object me)
{
    object ob;

    if( (int)me->query_skill("force", 1) < 30)
        return notify_fail("你的內功火候還不夠。\n");

    if( (int)me->query_skill("hammer", 1) < 50)
        return notify_fail("你的基本錘法水平太低。\n");

    if( query("max_neili", me)<250 )
        return notify_fail("你的內力不夠，不能練紫金錘法。\n");

    if ((int)me->query_skill("hammer", 1) < (int)me->query_skill("zijin-chuifa", 1))
        return notify_fail("你的基本錘法水平有限，無法領會更高深的紫金錘法。\n");

    if( !objectp(ob=query_temp("weapon", me) )
         || query("skill_type", ob) != "hammer" )
            return notify_fail("你使用的武器不對，無法練習紫金錘法。\n");

    return 1;
}

int valid_enable(string usage)
{
    return usage=="hammer" || usage=="parry";
}

mapping query_action(object me, object weapon)
{
    int i, level;
    level = (int)me->query_skill("zijin-chuifa", 1);
    for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    object ob;

    if( query("qi", me)<50 )
        return notify_fail("你的體力太低，沒有辦法練習紫金錘法。\n");

    if( query("neili", me)<50 )
        return notify_fail("你的內力不夠，沒有辦法練習紫金錘法。\n");

    if( !objectp(ob=query_temp("weapon", me) )
         || query("skill_type", ob) != "hammer" )
            return notify_fail("你使用的武器不對，無法練習紫金錘法。\n");

    me->receive_damage("qi", 45);
    addn("neili", -41, me);
    return 1;
}
