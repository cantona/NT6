#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "灰飛湮滅"; }

int perform(object me, object target)
{
        return SKILL_D("liuyang-zhang/hui")->perform(me, target);
}