
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "真命天子" NOR; }

int perform(object me, string skill, string arg)
{
      return notify_fail("這項技能不需要使用。\n");
}
