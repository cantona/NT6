#include <ansi.h>

inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "星宿派"; }

int valid_learn(object me)
{        
        if (me->query_skill("sanyin-wugongzhao", 1) < 30)
                return notify_fail("你三陰蜈蚣爪火候不足，無法研習冰蠶功。\n");        
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("冰蠶功只能星宿派弟子方可研習。\n");

        if (me->query_skill("bingchan-gong", 1) / 2 > me->query_skill("xingxiu-qishu", 1)) 
                return notify_fail("你星宿奇術等級不足，無法繼續研習冰蠶功。\n"); 

        return 1;
}

int difficult_level()
{
        return 2000;
}