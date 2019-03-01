#include <ansi.h>
// 魔教 motun-tianxia
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "魔教"; }

int valid_learn(object me)
{        
        if (me->query_skill("chiyou-kuangzhanjue", 1) < 120)
                return notify_fail("你蚩尤狂戰決火候不足，無法研習魔吞天下。\n");
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("魔吞天下只能魔教弟子方可研習。\n");

        if (me->query_skill("moon-blade", 1) < 150)
                return notify_fail("你圓月彎刀修為不足，無法繼續研習魔吞天下。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}
