#include <ansi.h>
// 歐陽世家 驅蛇
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "歐陽世家"; }

int valid_learn(object me)
{        
        if (me->query_skill("jiuyin-hamagong", 1) < 150)
                return notify_fail("你九陰蛤蟆功火候不足，無法研習驅蛇。\n");        
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("驅蛇只能歐陽世家弟子方可研習。\n");

        if (me->query_skill("baituo-michuan", 1) < 150)
                return notify_fail("你白駝秘傳等級不足，無法繼續研習驅蛇。\n");

        if (me->query_skill("training", 1) < 150)
                return notify_fail("你馭獸術等級不足，無法繼續研習驅蛇。\n");
        
        return 1;
}

int difficult_level()
{
        return 2000;
}