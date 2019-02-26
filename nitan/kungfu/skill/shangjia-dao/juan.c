#include <ansi.h>
#include <combat.h>

#define JUAN "「" HIW "寒芒暴卷" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if( userp(me) && !query("can_perform/shangjia-dao/juan", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(JUAN "只能對戰鬥中的對手使用。\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對，難以施展" JUAN "。\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的內功火候不夠，難以施展" JUAN "。\n");

        if ((int)me->query_skill("shangjia-dao", 1) < 50)
                return notify_fail("你的商家刀法還不到家，難以施展" JUAN "。\n");

        if (me->query_skill_mapped("blade") != "shangjia-dao")
                return notify_fail("你沒有激發商家刀法，難以施展" JUAN "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真氣不夠，難以施展" JUAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "手中" + weapon->name() +  HIW "吞吐不定，刀勢連環起"
              "伏，頓時疊起重重刀芒裹向$n" HIW "全身！\n" NOR;

        ap = me->query_skill("blade");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 3 + random(ap / 2);
                addn("neili", -80, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           HIR "$n" HIR "只覺得無數刀光攜着寒芒向"
                                           "自己湧來，一時躲閃不及，連中數刀！\n" NOR);
                me->start_busy(2);
        } else 
        {
                msg += CYN "可$p" CYN "身子一偏，向後橫移數尺，躲開了$P"
                       CYN "的攻勢。\n" NOR;
                addn("neili", -30, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}