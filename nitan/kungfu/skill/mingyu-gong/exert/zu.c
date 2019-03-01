// zu.c  by sinb

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用明玉功恢復自己的氣血。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你的真氣不夠！\n");

        if (me->query_condition("mingyu_qizu"))
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("mingyu-gong", 1);

        addn("neili", -100, me);

        message_combatd(HIC "$N" HIC "運起「氣足」奇功，"
                        "眼中閃過一片青芒，隨即恢復正常\n" NOR, me);


        me->apply_condition("mingyu_qizu", skill / 100);
        if (me->is_fighting()) me->start_busy(5);

        return 1;
}
