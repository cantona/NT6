// shan.c

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i;
        int n;
        string pmsg;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("小李飛刀只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
            query("skill_type", weapon) != "throwing" )
                return notify_fail("你現在手中並沒有拿著飛刀。\n");

        if ((skill = me->query_skill("xiaoli-feidao", 1)) < 100)
                return notify_fail("你的小李飛刀不夠嫻熟。\n");

        if( query("neili", me)<100 )
                return notify_fail("你內力不夠了。\n");

        addn("neili", -50, me);
        weapon->add_amount(-1);

        msg= HIW "忽然間只見$N" HIW "手中寒光一閃，正是小李飛刀，例無虛發！\n\n"
             NOR + HIR "一股鮮血從$n" HIR "嚥喉中噴出……\n" NOR;
        message_combatd(msg, me, target);


        me->start_busy(random(5));
        target->die(me);
        me->reset_action();
        return 1;
}