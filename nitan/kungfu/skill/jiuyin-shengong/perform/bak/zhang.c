// zhang.c 九陰神掌

#include <ansi.h>

inherit F_SSERVER;

#define ZHANG "「" HIM "九陰神掌" NOR "」"

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int i, times, count;

        if( userp(me) && !query("can_perform/jiuyin-shengong/zhang", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHANG "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("此招只能空手施展！\n");

        if ((int)me->query_skill("jiuyin-shengong", 1) < 260)
                return notify_fail("你的九陰神功不夠深厚，不會使用" ZHANG "。\n");

        if ((int)me->query_skill("strike", 1) < 220)
                return notify_fail("你的基本掌法修為不夠，不會使用" ZHANG "。\n");

        if (me->query_skill_prepared("unarmed") != "jiuyin-shengong"
           && me->query_skill_prepared("strike") != "jiuyin-shengong")
                return notify_fail("你沒有準備使用九陰神功，無法施展" ZHANG "。\n");

        if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "雙掌一錯，幻化出無數掌影，層層疊盪向$n"
              HIY "逼去！\n" NOR;

        ap = me->query_skill("jiujin-shengong", 1);
        dp = target->query_skill("parry", 1);

        if (ap / 2 + random(ap) > dp)
                count = ap / 7;
 
        else count = 9;

        addn_temp("apply/attack", count, me);
        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, );
        }
        me->start_busy(2 + random(4));
        addn("neili", -320, me);

        addn_temp("apply/attack", -count, me);
        message_combatd(msg, me, target);

        return 1;
}