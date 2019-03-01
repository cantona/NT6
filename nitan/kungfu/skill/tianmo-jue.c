// tianmo-jue.c 

inherit SKILL; 

#include <ansi.h> 

void create() { seteuid(getuid()); } 

string type() { return "knowledge"; } 

int practice_skill(object me) 
{
        return notify_fail("天魔訣只能靠學習來提高。\n");
}

void skill_improved(object me) 
{
        tell_object(me, HIR "殺!殺!殺！我要殺盡天下所有人!\n" NOR);
        addn("shen", -200, me);
}