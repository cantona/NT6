// xuwen-qixingding.c 虛蚊七星釘
// Edit By Vin On 26/2/2001

#include <ansi.h>

inherit SKILL;

int valid_learn(object me)
{
        object ob;
  
        if (me->query_skill("throwing", 1) < 20)
                return notify_fail("你的暗器技能不夠嫻熟。\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("xuwen-qixingding", 1))
                return notify_fail("你的基本暗器水平有限，難以領會更精妙的虛蚊七星釘。\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "throwing";
}

int practice_skill(object me)
{
        object weapon;

        if( query("qi", me)<110 )
                return notify_fail("你的體力不足練習虛蚊七星釘。\n");

        me->receive_damage("qi", 100);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"xuwen-qixingding/" + action;
}