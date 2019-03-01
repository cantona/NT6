
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIG "妙手藥王" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你對所有藥理及毒物運用出神入化，帶毒類攻擊對手，可使對手中毒程度加深20%；\n"
                           "同時，具有本草知識技能的特效，且效果提升10%。不需要運用。\n");
}

