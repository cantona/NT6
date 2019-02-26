// qiong 無窮無盡

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define QIONG "「" HIR "無窮無盡" NOR "」"

int perform(object me, object target)
{
        string msg;
        int ap, ap1, dp1, damage;
        mixed dp;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(QIONG "只能在戰鬥中對對手使用。\n");

        if (me->query_skill("kuihua-mogong", 1) < 250)
                return notify_fail("你的葵花魔功還不夠嫻熟，不能使用" QIONG "！\n");

        if( query("max_neili", me)<3800 )
                return notify_fail("你的內力修為不足，難以施展" QIONG "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，無法施展" QIONG "\n");

        if( weapon=query_temp("weapon", me) )
        {
                if( query("skill_type", weapon) != "sword" && 
                    query("skill_type", weapon) != "pin" )
                        return notify_fail("你手裏拿的不是劍，怎麼施"
                                           "展" QIONG "？\n");
        } else
        {
                if (me->query_skill_prepared("finger") != "kuihua-mogong")
                        return notify_fail("你並沒有準備使用葵"
                                           "花魔功，如何施展" QIONG "？\n");
        }
        if (weapon && me->query_skill_mapped("sword") != "kuihua-mogong")
                return notify_fail("你沒有準備使用葵花魔功，難以施展" QIONG "。\n");

        if (! weapon && me->query_skill_prepared("finger") != "kuihua-mogong")
                return notify_fail("你沒有準備使用葵花魔功，難以施展" QIONG "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIR "\n$N" HIR "尖嘯一聲，猛然進步欺前，一招竟直襲$n" HIR "要害，速度之快，令"
              "人見所未見，聞所未聞。\n" NOR;

        ap = attack_power(me, "unarmed");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                me->want_kill(target);
                ap = me->query_skill("kuihua-mogong", 1);
                dp=query("combat_exp", target)/10000;
                addn("neili", -60, me);
                me->start_busy(1 + random(2));

                if (dp >= 10000) // 對百萬經驗以上無效，但是仍然受到傷害
                {
                        if (weapon) damage = damage_power(me, "sword");
                        else damage = damage_power(me, "unarmed");
                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 95 + random(5),
                                                HIR "這一招速度之快完全超出了$n" HIR "的想象，$n" HIR
                                                "慌忙回縮招架，但是此招之快，已無從躲閃，$n" HIR "尖叫"
                                                "一聲，已然中招。\n" NOR);

                        message_sort(msg, me, target);
                        return 1;
                } else
                // if (random(ap) > dp)
                {
                        msg += HIR "這一招速度之快完全超出了$n" HIR "的想象，被$N"
                               HIR "這一招正好擊中了丹田要害，渾身真氣登時渙散！\n" NOR;
                        message_combatd(msg, me, target);
                        addn("neili", -120, me);
                        target->receive_damage("qi", 1, me);
                        target->die(me);
                        return 1;
                }

        } else
                msg += HIM "$n" HIM "大吃一驚，連忙退後，居然"
                                "僥倖躲開着這一招！\n" NOR;

        me->start_busy(1 + random(2));
        message_combatd(msg, me, target);

        return 1;
}