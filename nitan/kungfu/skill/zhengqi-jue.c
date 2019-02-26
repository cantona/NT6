// zhengqi-jue.c

inherit SKILL;

#include <ansi.h>

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int practice_skill(object me)
{
        return notify_fail("正氣決只能靠學(learn)來提高。\n");
}
void skill_improved(object me)
{
        tell_object(me, HIR "你心裏鼓盪着一股俠義之氣！\n" NOR );
        addn("shen", 200, me);
}


