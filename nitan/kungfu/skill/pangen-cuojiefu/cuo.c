#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "錯字訣" NOR; }

int perform(object me, object target)
{
        object weapon;
        int level;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "hammer" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((level = me->query_skill("pangen-cuojiefu", 1)) < 100)
                return notify_fail("你盤根錯節斧不夠嫻熟，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的內力修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("hammer") != "pangen-cuojiefu")
                return notify_fail("你沒有激發盤根錯節斧，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIR "$N" HIR "高舉手中" + weapon->name() + HIR "，陡然一聲斷喝，朝著$n"
              HIR "猛揮數斧，氣勢如虹。\n" NOR;

        addn("neili", -30, me);

        ap = attack_power(me, "hammer");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$p" HIR "見$P" HIR "來勢洶湧，不得不中途"
                       "變招，這一下登時便失了先機！\n" NOR;
                target->start_busy(level / 18 + 1);
        } else
        {
                msg += CYN "可是$p" CYN "看破$P" CYN "招式的來路，斜"
                       "斜跳開，使這招未起到絲毫作用。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}