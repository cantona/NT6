#include <ansi.h>

inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "逍遙派"; }

int valid_learn(object me)
{       
        if (me->query_skill("lingbo-weibu", 1) < 150)
                return notify_fail("你凌波微步功火候不足，無法研習逍遙遊。\n"); 

        if( query("family/family_name", me) != family_name() )
                return notify_fail("逍遙遊只能逍遙派弟子方可研習。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}
