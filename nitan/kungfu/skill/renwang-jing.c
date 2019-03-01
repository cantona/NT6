#include <ansi.h>
// 仁王經 renwang-jing
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "段氏皇族"; }

int valid_learn(object me)
{        
        if (me->query_skill("sun-finger", 1) < 30)
                return notify_fail("你一陽指火候不足，無法研習仁王經。\n");        
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("仁王經只能段氏皇族弟子方可研習。\n");

        if (me->query_skill("kurong-changong", 1) < 
            me->query_skill("renwang-jing", 1) * 60 /100)
                return notify_fail("你枯榮禪功修為不足，無法繼續研習仁王經。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}
