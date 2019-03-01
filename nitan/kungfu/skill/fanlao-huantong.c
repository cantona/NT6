#include <ansi.h>
// 靈鷲 fanlao-huantong
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "靈鷲宮"; }

int valid_learn(object me)
{        
        if (me->query_skill("bahuang-gong", 1) < me->query_skill("fanlao-huantong", 1))
                return notify_fail("你八荒六合唯我獨尊功火候不足，無法研習返老還童功。\n");        
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("返老還童功只能靈鷲宮弟子方可研習。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}