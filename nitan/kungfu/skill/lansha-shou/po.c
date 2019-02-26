#include <ansi.h>
#include <combat.h>

#define PO "「" HIB "破靛神砂" NOR "」"

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        int lvl;

        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/lansha-shou/po", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(PO "只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail(PO "只能空手施展。\n");

        if ((int)me->query_skill("lansha-shou", 1) < 100)
                return notify_fail("你藍砂手不夠熟練，難以施展" PO "。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內力修為不足，難以施展" PO "。\n");

        if (me->query_skill_mapped("hand") != "lansha-shou")
                return notify_fail("你沒有激發藍砂手，難以施展" PO "。\n");

        if (me->query_skill_prepared("hand") != "lansha-shou")
                return notify_fail("你沒有準備藍砂手，難以施展" PO "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不足，難以施展" PO "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIG "$N" HIG "身形急轉，宛若鬼魅，悄然施出藍砂手絕技「" NOR +
              HIB "破靛神砂" NOR + HIG "」，朝$n" HIG "胸前大穴抓落！\n" NOR;

        lvl = me->query_skill("lansha-shou", 1);

        ap = me->query_skill("hand");
        dp = target->query_skill("force");

        me->start_busy(3);
        if (ap / 2 + random(ap) > dp)
        { 
                damage = ap / 2 + random(ap / 3);
                addn("neili", -100, me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 20,
                                          (: final, me, target, damage :));
        } else
        {
                msg += CYN "$n" CYN "見$N"
                       CYN "來勢洶湧，奮力格擋，終於化解開來。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        int lvl = me->query_skill("lansha-shou", 1) / 2 * 3;

        target->affect_by("sha_poison",
                (["level":query("jiali", me)+random(query("jiali", me)),
                   "id":query("id", me),
                   "duration" : lvl / 50 + random(lvl / 30) ]));

        return HIR "$n" HIR "閃避不及，登被$N" HIR
               "抓出五道血痕，傷口竟滲出黑血，隱隱"
               "發着磷光。\n" NOR;
}
