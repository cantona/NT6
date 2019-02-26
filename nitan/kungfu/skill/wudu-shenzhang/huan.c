#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "千幻神訣" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((int)me->query_skill("wudu-shenzhang", 1) < 100)
                return notify_fail("你五毒神掌不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "wudu-shenzhang")
                return notify_fail("你沒有準備五毒神掌，難以施展" + name() + "。\n");

        if (me->query_skill("dodge") < 150)
                return notify_fail("你的輕功修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");

        msg = HIC "\n$N" HIC "身法陡然變快，使出絕招「" HIG "千幻神訣" HIC "」，"
              "雙掌不斷拍出，\n招式如影如幻，虛實難測，試圖擾亂$n" HIC "的攻"
              "勢。\n" NOR;

        message_combatd(msg, me, target);

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIY "$n" HIY "只見$N" HIY "雙掌飄忽不定，毫"
                      "無破綻，竟被困在$N" HIY "的掌風之中。\n" NOR;

                if( !target->is_busy() )
                        target->start_busy(ap / 90 + 1);
                me->start_busy(1);
                addn("neili", -80, me);
        } else
        {
                msg = CYN "$n" CYN "看破$N" CYN "毫無攻擊之意，於"
                      "是大膽反攻，將$N" CYN "這招盡數化解。\n" NOR;

                me->start_busy(2);
                addn("neili", -30, me);
        }
        message_combatd(msg, me, target);

        return 1;
}