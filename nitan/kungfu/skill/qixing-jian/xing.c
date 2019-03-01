#include <ansi.h>
#include <combat.h>

#define XING "「" HIY "群星璀璨" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/qixing-jian/xing", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(XING "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" XING "。\n");

        if (me->query_skill("qixing-jian", 1) < 60)
                return notify_fail("你七星劍法修為不夠，難以施展" XING "。\n");

        if (me->query_skill_mapped("sword") != "qixing-jian")
                return notify_fail("你沒有激發七星劍法，難以施展" XING "。\n");

        if (me->query_skill("force") < 80)
                return notify_fail("你內功的修為不夠，難以施展" XING "。\n");

        if( query("neili", me)<50 )
                return notify_fail("你現在的真氣不足，難以施展" XING "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "手中" + weapon->name() + HIY "一振，電光火石間"
              "連刺數劍，劍尖閃爍，化作點點繁星罩向$n" HIY "。\n" NOR;

        ap = me->query_skill("sword");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 3 + random(ap / 2);
                addn("neili", -30, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$n" HIR "頓時大吃一驚，格擋不及，"
                                           "登被$N" HIR "劍尖刺中，鮮血四濺！\n" NOR);
        } else
        {
                addn("neili", -20, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "並不慌亂，輕輕格擋開了$P"
                       CYN "的劍招。\n"NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}