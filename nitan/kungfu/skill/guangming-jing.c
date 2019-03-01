#include <ansi.h>
// 明教 guangming-jing
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "明教"; }

int valid_learn(object me)
{        
        if (me->query_skill("jiuyang-shengong", 1) < 120)
                return notify_fail("你九陽神功火候不足，無法研習大雲光明經。\n");
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("大雲光明經只能明教弟子方可研習。\n");

        if (me->query_skill("qiankun-danuoyi", 1) < 150)
                return notify_fail("你乾坤大挪移修為不足，無法繼續研習大雲光明經。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}
