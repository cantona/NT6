#include <ansi.h>
// 五毒教五毒阱 wudu-jing
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "五毒教"; }

int valid_learn(object me)
{        
        if (me->query_skill("wudu-qishu", 1) < 200)
                return notify_fail("你五毒奇術火候不足，無法研習五毒阱。\n");        
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("五毒阱只能五毒教弟子方可研習。\n");

        if (me->query_skill("qianzhu-wandushou", 1) < 180)
                return notify_fail("你千蛛萬毒手修為不足，無法繼續研習五毒阱。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}