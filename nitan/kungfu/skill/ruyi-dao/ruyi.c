// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIC "如意六刀" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, skill;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你的武器不對，難以施展" + name() + "。\n");

        if( query("neili", me)<250 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if (me->query_skill("ruyi-dao", 1) < 100)
                return notify_fail("你的如意刀法還不到家，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "ruyi-dao")
                return notify_fail("你沒有激發如意刀法，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIC "$N" HIC "使出逍遙絕技「如意六刀」，身法忽然奇快無比，變幻莫測！\n" NOR;
        message_combatd(msg, me);
        addn("neili", -120, me);
        skill = me->query_skill("ruyi-dao", 1);
        addn_temp("apply/attack", skill/2, me);
        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        addn_temp("apply/attack", -skill/2, me);
        me->start_busy(1 + random(3));

        return 1;
}
