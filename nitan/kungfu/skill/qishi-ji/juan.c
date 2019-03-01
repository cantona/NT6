#include <ansi.h>
#include <combat.h>

#define JUAN "「" HIY "旋轉卷刺" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if( userp(me) && !query("can_perform/qishi-ji/juan", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(JUAN "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "club" )
                return notify_fail("你所使用的武器不對，難以施展" JUAN "。\n");

        if (me->query_skill("qishi-ji", 1) < 100)
                return notify_fail("你聖騎士戟修為不夠，難以施展" JUAN "。\n");

        if (me->query_skill_mapped("club") != "qishi-ji")
                return notify_fail("你沒有激發聖騎士戟，難以施展" JUAN "。\n");

        if (me->query_skill("force") < 150)
                return notify_fail("你的內功修為不夠，難以施展" JUAN "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，難以施展" JUAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "連退數步，手中" + weapon->name() + HIY "急速旋"
              "轉，戟尖頓時激起一股氣流，直刺$n" HIY "而去！\n" NOR;

        ap = me->query_skill("club");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap + random(ap);
                addn("neili", -50, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "結果$n" HIR "躲閃不慎，被$N" HIR
                                           "的" + weapon->name() + HIR "戟尖刺中"
                                           "要害，登時鮮血飛濺！\n" NOR);
        } else
        {
                addn("neili", -30, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "並不慌亂，收斂心神，閃避開了$P"
                       CYN "的疾刺攻擊。\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
