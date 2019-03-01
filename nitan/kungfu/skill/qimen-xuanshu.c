#include <ansi.h>

inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "桃花島"; }

int valid_learn(object me)
{        
        
        if (me->query_skill("qimen-wuxing", 1) < 100)
                return notify_fail("你奇門五行掌握得不夠。\n");

        if( query("family/family_name", me) != family_name() )
                return notify_fail("奇門玄術只能桃花島弟子方可研習。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}