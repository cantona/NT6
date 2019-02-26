#include <ansi.h>
#include <combat.h>

#define SHE "「" HIR "拔槍狼牙射擊" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i;

        if( userp(me) && !query("can_perform/gun/she", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHE "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "hammer" )
                return notify_fail("你使用的武器不對，難以施展" SHE "。\n");

        if ((int)me->query_skill("gun", 1) < 80)
                return notify_fail("你的槍械技術不夠熟練，難以施展" SHE "。\n");

        if (me->query_skill_mapped("hammer") != "gun")
                return notify_fail("你並沒有運用槍械技術，難以施展" SHE "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIR "$N" HIR "施出祕奧義「拔槍狼牙射擊」，手中" + weapon->name() +
              HIR "連續數槍，同時噴出數十條火龍罩向$n" HIR "四周！\n\n" NOR;
        message_combatd(msg, me, target);

        for (i = 0; i < 18; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1);
        return 1;
}