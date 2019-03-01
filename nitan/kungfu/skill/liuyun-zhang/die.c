#include <ansi.h>
#include <combat.h>

#define DIE "「" HIW "流雲疊影" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if( userp(me) && !query("can_perform/liuyun-zhang/die", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(DIE "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(DIE "只能空手施展。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((int)me->query_skill("liuyun-zhang", 1) < 100)
                return notify_fail("你流雲掌不夠嫻熟，難以施展" DIE "。\n");

        if (me->query_skill_mapped("strike") != "liuyun-zhang")
                return notify_fail("你沒有激發流雲掌，難以施展" DIE "。\n");

        if (me->query_skill_prepared("strike") != "liuyun-zhang")
                return notify_fail("你沒有準備流雲掌，難以施展" DIE "。\n");

        if (me->query_skill("dodge") < 150)
                return notify_fail("你的輕功修為不夠，難以施展" DIE "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，難以施展" DIE "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        ap = me->query_skill("liuyun-zhang", 1) +
             me->query_skill("dodge", 1) / 2;

        dp = target->query_skill("dodge");

        msg = HIC "\n$N" HIC "身法陡然變快，雙掌不斷拍出，招式如影"
              "如幻，虛實難測，試圖擾亂$n" HIC "的攻勢。" NOR;

        message_sort(msg, me, target);

        if (random(ap) > dp / 2)
        {
                msg = HIY "$n" HIY "只見$N" HIY "雙掌飄忽不定，毫"
                      "無破綻，竟被困在$N" HIY "的掌風之中。\n" NOR;

                target->start_busy(ap / 45 + 1);
                       me->start_busy(1);
                addn("neili", -80, me);
        } else
        {
                msg = CYN "$n" CYN "看破$N" CYN "毫無攻擊之意，于"
                      "是大膽反攻，將$N" CYN "這招盡數化解。\n" NOR;

                me->start_busy(2);
                addn("neili", -30, me);
        }
        message_combatd(msg, me, target);

        return 1;
}