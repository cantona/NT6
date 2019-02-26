//meiying-jian 魅影劍法
// Made by deaner
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([  "action" : "$N手中$w虛晃了數下，跟着猛然刺向$n的$l，去勢疾若閃電",
    "force" : 60,
    "damage":100,
    "dodge" : 20,
    "lvl"   : 60,
    "skill_name" : "無中生有",
    "damage_type" : "刺傷"
]),
([  "action" : "$N手中的$w不住的顫動，看似指向$n的$l，忽又改挑$n的$l",
    "force"  : 80,
    "dodge"  : 35,
    "damage" : 100,
    "lvl"    : 100,
    "skill_name" : "鬼影重重",
    "damage_type" : "刺傷"
]),
([  "action" : "$N手中的$w連連晃動，去向變幻不定，最後突然直刺$n的$l",
    "force"  : 100,
    "dodge"  : 55,
    "damage" :100,
    "lvl"    : 140,
    "skill_name" : "如鬼似魅",
    "damage_type" : "刺傷"
]),
([  "action" : "$N手中的$w猛然縮回身側，隨即刺向$n的$l，去勢兇猛異常",
    "force"  : 120,
    "dodge"  : 75,
    "damage" : 100,
    "lvl"    : 160,
    "skill_name" : "化虛為實",
    "damage_type" : "刺傷"
]),
([  "action" : "$N滑步錯身，手中$w一沉一收，跟着斜斜揮出，疾挑$n的$l",
    "force"  : 140,
    "dodge"  : 90,
    "damage" : 100,
    "lvl"    : 200,
    "skill_name" : "壓露啼煙",
    "damage_type" : "刺傷"
]),
([  "action" : "$N大喝一聲，手中$w陡然幻出漫天光影，閃電般刺向$n的$l",
    "force"  : 160,
    "dodge"  : 100,
    "damage" : 100,
    "lvl"    : 220,
    "skill_name" : "掃月拂雲",
    "damage_type" : "刺傷"
]),
([  "action" : "$N斜跨兩步，旋即回身發力，手中$w斜斜刺出，攻向$n的$l",
    "force"  : 170,
    "dodge"  : 120,
    "damage" : 100,
    "lvl"    : 260,
    "skill_name" : "星光密射",
    "damage_type" : "刺傷"
]),
([  "action" : "$N身形一變，手中$w忽地出擊，迅疾無比的向$n$l直刺過去",  
    "force"  : 180,
    "dodge"  : 150,
    "damage" : 100,
    "lvl"    : 300,
    "skill_name" : "風馳電掣",
    "damage_type" : "刺傷"
]),
});


int valid_enable(string usage) { return usage == "sword" || usage == "parry"; } 

int valid_learn(object me)
{
    if ((int)me->query("max_neili") < 2500)
        return notify_fail("你的內力不夠。\n");

    if ((int)me->query_skill("force") < 200)
        return notify_fail("你的內功心法火候太淺。\n");

    if ((int)me->query_skill("dodge") < 200)
        return notify_fail("你的輕功火候太淺。\n");

    if ((int)me->query_dex() < 40)
        return notify_fail("你的後天身法還不夠靈活。\n");

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
    level   = (int) me->query_skill("meiying-jian",1);
    for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    object weapon;

    if (me->query_skill("meiying-jian", 1) >= 400)
        return notify_fail("以你目前的修為只能通過研究該技能才能再有所提高。\n");

    if (!objectp(weapon = me->query_temp("weapon"))
    || (string)weapon->query("skill_type") != "sword")
        return notify_fail("你使用的武器不對。\n");

    if ((int)me->query("qi") < 100)
        return notify_fail("你的體力不夠練魅影劍法。\n");

    if ((int)me->query("neili") < 100)
        return notify_fail("你的內力不夠練魅影劍法。\n");

    me->receive_damage("qi", 80);
    me->add("neili", -80);

    return 1;
}

string perform_action_file(string action)
{
    return __DIR__"meiying-jian/" + action;
}

