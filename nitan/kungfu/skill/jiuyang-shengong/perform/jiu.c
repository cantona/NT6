// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "九曦混陽" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count;
        int i;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail(name() + "只能空手施展。\n");

        if (query("max_neili", me) < 6000)
                return notify_fail("你的內力的修為不夠，現在無法使用" + name() + "。\n");

        if (me->query_skill("jiuyang-shengong", 1) < 200)
                return notify_fail("你的九陽神功還不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "jiuyang-shengong")
                return notify_fail("你現在沒有激發九陽神功為拳腳，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("你現在沒有激發九陽神功為內功，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "jiuyang-shengong")
                return notify_fail("你現在沒有準備使用九陽神功，難以施展" + name() + "。\n");

        if ((int)query("neili", me) < 500)
                return notify_fail("你的真氣不夠，無法運用" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIR "$N" HIR "大喝一聲，頓時一股浩蕩無比的真氣至體內迸發，雙掌"
              "猛然翻滾，朝$n" HIR "閃電般拍去。\n" NOR;

        ap = attack_power(me, "unarmed") + me->query_con();
        dp = defense_power(target, "parry") + target->query_con();

        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 9;
                msg += HIR "$n" HIR "只覺周圍空氣熾熱無比，又見無數氣團向"
                       "自己襲來，頓感頭暈目眩，不知該如何抵擋。\n" NOR;
        } else
        {
                msg += HIY "$n" HIY "只見$N" HIY "無數氣團向自己襲來，連"
                       "忙強振精神，勉強抵擋。\n" NOR;
                count = 0;
        }

        message_vision(msg, me, target);
        addn_temp("apply/attack", count, me);
        addn_temp("apply/unarmed_damage", count, me);

        addn("neili", -300, me);

        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(1 + random(3));
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/unarmed_damage", -count, me);

        return 1;
}