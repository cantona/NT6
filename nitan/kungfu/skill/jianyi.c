#include <ansi.h>
// 華山派 jianyi
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "華山派"; }

int valid_learn(object me)
{        
        if (me->query_skill("zixia-shengong", 1) < 120)
                return notify_fail("你紫霞神功火候不足，無法研習劍意。\n");
        
        if( query("family/family_name", me) != family_name() && query("family/family_name", me) != "華山劍宗" )
                return notify_fail("劍意只能華山派弟子方可研習。\n");

        if (me->query_skill("huashan-sword", 1) < 150)
                return notify_fail("你華山劍法修為不足，無法繼續研習劍意。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}
