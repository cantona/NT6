#include <ansi.h>

inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "昆侖派"; }

int valid_learn(object me)
{        
        if (me->query_skill("qiankun-jian", 1) < 120)
                return notify_fail("你乾坤神劍火候不足，無法研習昆侖無極。\n");        

        if( query("family/family_name", me) != family_name() )
                return notify_fail("昆侖無極只能昆侖派弟子方可研習。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}