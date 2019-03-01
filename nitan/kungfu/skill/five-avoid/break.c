// break.c 五遁絕殺

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int count;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「五遁絕殺」只能在戰鬥中使用。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的氣不夠，無法施展「五遁絕殺」！\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的內功火候不夠，難以施展「五遁絕殺」！\n");

        if( query("neili", me)<query("max_neili", me)/2 )
                return notify_fail("你的真氣不夠，無法施展「五遁絕殺」！\n");

        msg = HIC "$N" HIC "使出五行遁中的「五遁絕殺」，身法"
              "陡然間變得變幻莫測！\n" NOR;

        message_combatd(msg, me);
        count = (int)me->query_skill("five-avoid") / 30 + 2;
        if (count > 5 ) count = 5;

        while (count--)
        {
                if (! target || (environment(target) != environment(me)) ||
                    ! me->is_fighting(target) ||
                    query("qi", me)<20 || 
                    query("neili", me)<20 )
                {
                        message_combatd(WHT "$N" WHT "的身形倏地一"
                                        "轉，收身停住了腳步。\n" NOR, me);
                        break;
                } else

                message_combatd(WHT "$N" WHT "的身影在$n"
                                WHT "身旁時隱時現 ...\n" NOR, me, target);
                if (! COMBAT_D->fight(me, target))
                        message_combatd(WHT "但是$N" WHT "始終沒有找到機會出手！\n" NOR, me);
                me->receive_damage("qi", 10);
                addn("neili", -10, me);
        }

        me->start_busy(1);
        return 1;
}