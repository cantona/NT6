#include <ansi.h>
#include <combat.h>

#define SUO "「" HIW "煙雲鎖身" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg, wp, wp2;
        object weapon, weapon2;
        int ap, dp;

        if( userp(me) && !query("can_perform/tianzhu-jian/suo", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(SUO "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" SUO "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((int)me->query_skill("tianzhu-jian", 1) < 120)
                return notify_fail("你天柱劍法不夠嫻熟，難以施展" SUO "。\n");

        if (me->query_skill_mapped("sword") != "tianzhu-jian")
                return notify_fail("你沒有激發天柱劍法，難以施展" SUO "。\n");

        if (me->query_skill("dodge") < 150)
                return notify_fail("你的輕功修為不夠，難以施展" SUO "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，難以施展" SUO "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        wp = weapon->name();
        ap = me->query_skill("tianzhu-jian", 1);
        dp = target->query_skill("parry", 1);

        if( query("max_neili", me)>query("max_neili", target)*3/2
            && objectp(weapon2=query_temp("weapon", target)) )
        {
                wp2 = weapon2->name();

                msg = HIW "\n$N" HIW "劍法陡然變快，施展出「煙雲鎖身劍」，手中" +
                      wp + HIW "幻作一道白芒，撩向$n" HIW "所持的" + wp2 + HIW
                      "。" NOR;

                message_sort(msg, me, target);

                       me->start_busy(2);
                       addn("neili", -200, me);

                if (random(ap) > dp / 2)
                {
                        msg = HIR "$n" HIR "只見眼前白芒暴漲，登時右手一輕，"
                              + wp2 + HIR "竟脫手飛出。\n" NOR;

                        target->start_busy(3);
                        weapon2->move(environment(target));
                } else
                {
                        msg += CYN "可是$n" CYN "看破$N" CYN "劍法中的虛招，鎮"
                               "定自如，從容應對。\n" NOR;
                }
        } else
        {
                msg = HIC "\n$N" HIC "劍法陡然變快，施展出「" HIW "煙雲鎖身劍"
                      HIC "」，手中" + wp + HIC "劍光奪目，欲將$n" HIC "籠罩在"
                      "劍光之中。" NOR;

                       me->start_busy(1);
                addn("neili", -100, me);

                if (random(ap) > dp / 2)
                {
                        msg += HIR "\n$n" HIR "驚慌不定，頓時亂了陣腳，竟被困于$N"
                               HIR "的劍光當中。" NOR;

                        target->start_busy(ap / 25 + 1);
                } else
                {
                        msg += CYN "\n可是$n" CYN "看破$N" CYN "劍法中的虛招，鎮"
                               "定自如，從容應對。" NOR;
                }
        }
        message_combatd(msg, me, target);
        return 1;
}