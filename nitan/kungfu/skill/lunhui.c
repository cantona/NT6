#include <ansi.h>

inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "少林派"; }

int valid_learn(object me)
{        
        if (me->query_skill("buddhism", 1) < 200)
                return notify_fail("你禪宗心法修為不足，無法研習六道輪回之術。\n");        
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("六道輪回之術只能少林派弟子方可研習。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}
