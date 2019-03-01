#include <ansi.h>

inherit SKILL;

int valid_learn(object me)
{
        object ob;
  
        if (me->query_skill("throwing", 1) < 40)
                return notify_fail("你的暗器技能不夠嫻熟。\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("furong-jinzhen", 1))
                return notify_fail("你的基本暗器水平有限，難以領會更精妙的芙蓉金針。\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "throwing";
}

int practice_skill(object me)
{
        if( query("qi", me)<80 )
                return notify_fail("你的氣不夠，沒有辦法練習芙蓉金針。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠，沒有辦法練習芙蓉金針。\n");

        me->receive_damage("qi", 70);
        addn("neili", -50, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"furong-jinzhen/" + action;
}