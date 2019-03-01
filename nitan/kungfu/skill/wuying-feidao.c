// Last Modified by winder on Sep. 12 2001
// wuying-feidao.c 無影飛刀

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action": "$N雙手一晃，手中的$w如一條銀蛇般飛向$n的$l",
        "force" : 20,
        "dodge" : -20,
        "damage": 90,
        "damage_type": "刺傷",
        "post_action": (: call_other, WEAPON_D, "throw_weapon" :),
]),
([      "action": "$N右手一抖，$w發出刺耳的破空聲直射$n的$l",
        "force" : 120,
        "dodge" : -30,
        "damage": 190,
        "damage_type": "刺傷",
        "post_action": (: call_other, WEAPON_D, "throw_weapon" :),
]),
([      "action": "$N手指微動，$w斜斜的飛向$n的$l",
        "force" : 220,
        "dodge" : -20,
        "damage": 290,
        "damage_type": "刺傷",
        "post_action": (: call_other, WEAPON_D, "throw_weapon" :),
]),
([      "action": "$N力發肩肘，右手一甩，手中的$w化作一道弧光射向$n的$l",
        "force" : 320,
        "dodge" : -40,
        "damage": 390,
        "damage_type": "刺傷",
        "post_action": (: call_other, WEAPON_D, "throw_weapon" :),
]),
});

int valid_enable(string usage) { return usage=="throwing" ; }
int valid_learn(object me)
{
        object ob;

        if( query("max_neili", me)<500 )
                return notify_fail("你的內力不夠，沒有辦法練無影飛刀。\n");
        if( !(ob=query_temp("weapon", me)) || 
                query("skill_type", ob) != "throwing" )
                return notify_fail("你必須先找一些暗器才能練無影飛刀。\n");
        if ((int)me->query_skill("honghua-shengong", 1) < 50)
                return notify_fail("你的紅花神功火候不夠，無法學無影飛刀。\n");

        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<30 || query("neili", me)<50 )
                return notify_fail("你的內力或氣不夠，沒辦法練習無影飛刀。\n");
        me->receive_damage("qi", 30);
        addn("neili", -30, me);
  //      write("你按著所學練了一遍無影飛刀。\n");
        return 1;
}
mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}
int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 15; }
int power_point(object me) { return 1; }

string perform_action_file(string action)
{
        return  __DIR__"wuying-feidao/" + action;
}
 
int help(object me)
{
        write(HIM"\n無影飛刀："NOR"\n");
        write(@HELP

    無影飛刀為神刀駱元通的家傳功夫。駱元通之女駱冰便是
紅花會的文四奶奶。

        學習要求：
                紅花神功50級
                內力修為500
HELP
        );
        return 1;
}