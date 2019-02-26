// This program is a part of NITAN MudLIB
// shang.c 傷字訣

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "傷字訣" NOR; }

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

        if ((int)me->query_skill("qishang-quan", 1) < 120)
                return notify_fail("你的七傷拳不夠嫻熟，無法施展" + name() + "。\n");

        if ((int)me->query_skill("force", 1) < 120)
                return notify_fail("你的內功修為還不夠，無法施展" + name() + "\n");

        if ((int)query("neili", me) < 300)
                return notify_fail("你現在真氣不夠，無法施展" + name() + "。\n");

        if (me->query_skill_prepared("cuff") != "qishang-quan")
                return notify_fail("你沒有準備使用七傷拳，無法施展" + name() + "。\n");

        if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$N" HIY "怒喝一聲，施出絕招「" HIW "傷字訣" HIY "」，雙拳迅猛無比"
              "的襲向$n" HIY "。\n" NOR;

        ap = attack_power(me, "cuff") +
             me->query_con() * 20;

        dp = defense_power(target, "parry") +
             target->query_con() * 20;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "cuff");
                damage+= query("jiali", me);
                addn("neili", -260, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 120,
                                           HIR "只見$P" HIR "這一拳把$p" HIR
                                           "飛了出去，重重的摔在地上，吐血不止！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "可是$p" HIC "奮力招架，硬生生的擋開了$P"
                       HIC "這一招。\n"NOR;
                addn("neili", -120, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
