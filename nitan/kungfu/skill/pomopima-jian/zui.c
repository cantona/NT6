#include <ansi.h>
#include <combat.h>

#define ZUI "「" HIR "醉裡乾坤" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/pomopima-jian/zui", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZUI "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器無法施展" ZUI "。\n");

        if (me->query_skill("force") < 150)
                return notify_fail("你的內功的修為不夠，無法施展" ZUI "。\n");

        if (me->query_skill("pomopima-jian", 1) < 120)
                return notify_fail("你的潑墨披麻劍修為不夠，無法施展" ZUI "。\n");

        if( query("neili", me)<250 )
                return notify_fail("你的真氣不夠，無法施展" ZUI "。\n");

        if (me->query_skill_mapped("sword") != "pomopima-jian") 
                return notify_fail("你沒有激發潑墨披麻劍，無法使用" ZUI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIR "$N" HIR "一聲長吟，手中" + weapon->name() + NOR + HIR
              "連劃三個圓圈，幻作三個光圈，便如是有形之物，緩緩向$n" HIR
              "身前移去！\n" NOR;

        ap = me->query_skill("sword");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap / 2);
                addn("neili", -200, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "$n" HIR "只覺劍氣滿室，寒風襲體，"
                                           "微微一楞，已連中三劍，鮮血飛濺！\n" NOR );
        } else
        {
                addn("neili", -100, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "見來勢迅猛，飛身一躍，"
                       "閃開了$P" CYN "這凌厲的幾劍。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}