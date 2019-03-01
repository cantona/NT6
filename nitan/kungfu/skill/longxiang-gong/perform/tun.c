// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return  HIR "龍吞勢" NOR; }

inherit F_SSERVER;

inherit F_CLEAN_UP;

void remove_effect(object me);

int perform(object me, object target)
{
        object weapon;
        int ap, dp, foc, damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if( query_temp("long_tun", me) )
                return notify_fail(name() + "無法連續施展。\n");

        if ((int)me->query_skill("longxiang-gong", 1) < 180)
                return notify_fail("你的龍象般若功修為不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "longxiang-gong")
                return notify_fail("你沒有激發龍象般若功為拳腳，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "longxiang-gong")
                return notify_fail("你沒有激發龍象般若功為內功，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "longxiang-gong")
                return notify_fail("你沒有準備使用龍象般若功，難以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "雙臂左右分張，形若龍嘴，所施正是龍象般若功絕學「"
              HIR "龍吞勢" HIY "」。霎時呼\n嘯聲大作，但見一股澎湃無比的罡勁"
              "至$N" HIY "雙掌間湧出，雲貫向$n" HIY "而去。\n" NOR;

        set_temp("long_tun", 1, me);
        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), 50);

        ap = attack_power(me, "unarmed") + me->query_skill("force");
        dp = defense_power(target, "dodge") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                foc = target->query_skill("force");
                damage = damage_power(me, "unarmed") + random(foc);
                damage+= query("jiali", me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 65,
                                               HIR "$n" HIR "一聲哀嚎，被$N" HIR "的罡"
                                               "氣劃中氣門，真氣在體內四處亂竄，慘不堪"
                                               "言。\n" NOR);

                me->start_busy(4);
                addn("neili", -300, me);
        } else
        {
                me->start_busy(5);
                addn("neili", -200, me);
                msg += CYN "可是$p" CYN "見$P" CYN "此招來勢非凡，急"
                       "忙向後橫移數尺，終于躲避開來。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

void remove_effect(object me)
{
        if( query_temp("long_tun", me) )
        {
                delete_temp("long_tun", me);
                tell_object(me, "你經過調氣養息，又可以繼續施展" + name() + "了。\n");
        }
}

