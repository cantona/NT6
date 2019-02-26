#include <ansi.h>

inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "崑崙派"; }

int valid_learn(object me)
{        
        if (me->query_skill("qiankun-jian", 1) < 120)
                return notify_fail("你乾坤神劍火候不足，無法研習崑崙無極。\n");        

        if( query("family/family_name", me) != family_name() )
                return notify_fail("崑崙無極只能崑崙派弟子方可研習。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}