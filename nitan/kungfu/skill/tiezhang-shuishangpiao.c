#include <ansi.h>
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "鐵掌幫"; }

int valid_learn(object me)
{        

        if( query("family/family_name", me) != family_name() )
                return notify_fail("鐵掌水上漂只能鐵掌幫弟子方可研習。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}