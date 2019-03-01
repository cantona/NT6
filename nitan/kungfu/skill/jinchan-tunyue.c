#include <ansi.h>
// 金蟾吞月 jinchan-tunyue
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "歐陽世家"; }

int valid_learn(object me)
{        
        if (me->query_skill("hamagong", 1) < 30)
                return notify_fail("你蛤蟆功火候不足，無法研習金蟾吞月。\n"); 
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("金蟾吞月只能歐陽世家弟子方可研習。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}
