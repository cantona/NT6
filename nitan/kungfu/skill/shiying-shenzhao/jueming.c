// jueming.c

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "絕命"; }

int perform(object me)
{
        string msg;
        object weapon, target;
        int ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「絕命」只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("你只能空手使用「絕命」。\n");

        ap = attack_power(me, "claw");

        if (ap < 150)
                return notify_fail("你的弒鷹神爪等級不夠, 無法使用「絕命」！\n");

        if( query("neili", me)<180 )
                return notify_fail("你的真氣不夠，無法運用「絕命」！\n");

        msg = HIR "$N" HIR "一聲暴喝，手臂上青筋突起，左手一晃，右手成爪，向$n" HIR
              "前胸迅疾抓到。\n" NOR;

        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -150, me);
                damage = damage_power(me, "claw");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                           HIR "$n" HIR "閃避不及，前胸頓時被抓出"
                                           "五條血痕，不禁長聲慘呼！\n" NOR);
                me->start_busy(2 + random(2));
        } else
        {
                addn("neili", -50, me);
                damage = damage_power(me, "claw") / 5;
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
                                           HIM "$n" HIM "不敢小覷此招，拼力拆解，"
                                           "但雙臂仍被抓出了幾條血印！\n" NOR);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}
