#include <ansi.h>
// 日出東方 richu-dongfang
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "日月神教"; }

int valid_learn(object me)
{        
        if (me->query_skill("riyue-jian", 1) < 30)
                return notify_fail("你日月劍法不足，無法研習日出東方。\n");
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("日出東方只能日月神教弟子方可研習。\n");

        if (me->query_skill("riyue-xinfa", 1) < 
            me->query_skill("richu-dongfang", 1) * 60 /100)
                return notify_fail("你日月心法修為不足，無法繼續研習日出東方。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}
