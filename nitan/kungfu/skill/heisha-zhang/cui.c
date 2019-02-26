#include <ansi.h>
#include <combat.h>

#define CUI "「" HIB "催魂掌" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        int lvl;

        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/heisha-zhang/cui", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(CUI "只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用" CUI "。\n");

        if (me->query_skill_mapped("strike") != "heisha-zhang")
                return notify_fail("你沒有激發黑砂掌，難以施展" CUI "。\n");

        if (me->query_skill_prepared("strike") != "heisha-zhang")
                return notify_fail("你現在沒有準備使用黑砂掌，難以施展" CUI "。\n");

        if ((int)me->query_skill("heisha-zhang", 1) < 100)
                return notify_fail("你的黑砂掌不夠熟練，難以施展" CUI "。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內力修為不足，難以施展" CUI "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，難以施展" CUI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIB "$N" HIB "冷笑數聲，單掌陡然一振，催魂般悄然拍至$n"
              HIB "前胸，不着半點力道。\n" NOR;  

        lvl = me->query_skill("heisha-zhang", 1);

        ap = me->query_skill("strike");
        dp = target->query_skill("force");

        me->start_busy(3);
        if (ap / 2 + random(ap) > dp)
        { 
                damage = ap / 2 + random(ap / 3);
                addn("neili", -100, me);
                target->affect_by("sha_poison",
                               (["level":query("jiali", me)+random(query("jiali", me)),
                                  "id":query("id", me),
                                  "duration" : lvl / 50 + random(lvl / 20) ]));
                                  msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
                                         damage, 20, HIR "$n" HIR "只覺$N" HIR "掌勁穿"
                                         "胸而過，一時説不出的難受，嘔出一大口黑血。\n"
                                         NOR);
        } else
        {
                msg += CYN "$n" CYN "見$N"
                       CYN "來勢洶湧，奮力格擋，終於化解開來。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}