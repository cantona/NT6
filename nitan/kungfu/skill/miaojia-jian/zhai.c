#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { HIW "雲邊摘月" NOR; }

int perform(object me, object target)
{
        object weapon;
        int level, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((level = me->query_skill("miaojia-jian", 1)) < 100)
                return notify_fail("你苗家劍法不夠嫻熟，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的內力修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "miaojia-jian")
                return notify_fail("你沒有激發苗家劍法，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "一聲清哮，劍勢舒張，吞吐不定，瞬間向$n" HIW "連刺"
              "數劍，企圖擾亂$n" HIW "的攻勢。\n" NOR;

        addn("neili", -30, me);
        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "結果$p" HIR "只見$P" HIR "劍招精妙，全然"
                       "辨不清招中虛實，攻勢登時一緊！\n" NOR;
                target->start_busy(level / 80 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "劍勢的來路，"
                       "徑自出招，絲毫不為所動。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}