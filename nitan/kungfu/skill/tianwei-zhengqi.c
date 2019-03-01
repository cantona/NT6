#include <ansi.h>
// 武當派 tianwei-zhengqi
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "武當派"; }

int valid_learn(object me)
{        
        if( query("shen", me)<1000000 )
                return notify_fail("你行俠仗義的事做得還不夠，現在還無法領悟天威正氣。\n");        
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("天威正氣只能武當派弟子方可研習。\n");

        if (me->query_skill("taiji-jian", 1) < 150)
                return notify_fail("你太極劍法修為不足，無法繼續研習天威正氣。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}