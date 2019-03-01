#include <ansi.h>
// 峨嵋 靜心 jingxin
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "峨嵋派"; }

int valid_learn(object me)
{        
        if (me->query_skill("huifeng-jian", 1) < 30)
                return notify_fail("你回風拂柳劍火候不足，無法研習靜心。\n");        
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("靜心只能峨嵋派弟子方可研習。\n");

        if (me->query_skill("jingxin", 1) / 2 > me->query_skill("mahayana", 1))
                return notify_fail("你大乘涅磐功等級不足，無法繼續研習靜心。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}