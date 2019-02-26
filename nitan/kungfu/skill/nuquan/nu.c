// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return MAG "一怒殺佛" NOR; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("nuquan", 1) < 40)
                return notify_fail("你的怒拳不夠嫻熟，無法施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在真氣不夠，無法施展" + name() + "。\n");

        if (me->query_skill_prepared("cuff") != "nuquan")
                return notify_fail("你沒有準備使用怒拳，無法施展" + name() + "。\n");

        if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$N" HIY "拳勁如芒、使拳如雷、拳氣如風、拳風如霧，拳勁彷佛無所不在，狠狠打擊$n"
              HIY "的視、聽、聞、味、觸五覺。\n" NOR;

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "cuff");

                addn("neili", -120, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 75,
                                           HIR "頓時$n" HIR "防守大受影響，只見$N" HIR "這一拳把$n" HIR
                                           "飛了出去，重重的摔在地上，吐血不止！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "可是$p" HIC "奮力招架，硬生生的擋開了$P"
                       HIC "這一招。\n"NOR;
                addn("neili", -80, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
