#include <ansi.h>
#include <combat.h>

#define SUN "「" HIR "損筋訣" NOR "」"

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object target;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( userp(me) && !query("can_perform/sanyin-shou/sun", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        skill = me->query_skill("sanyin-shou", 1);

        if (! target || ! me->is_fighting(target))
                return notify_fail(SUN "只能對戰鬥中的對手使用。\n");

        if (skill < 140)
                return notify_fail("你的三陰手等級不夠，難以施展" SUN "。\n");

        if( query("max_neili", me)<1600 )
                return notify_fail("你的內力修為不足，難以施展" SUN "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的內力不夠，難以施展" SUN "。\n");

        if (me->query_skill_mapped("hand") != "sanyin-shou")
                return notify_fail("你沒有激發三陰手，難以施展" SUN "。\n");

        if (me->query_skill_prepared("hand") != "sanyin-shou")
                return notify_fail("你現在沒有準備使用三陰手，難以施展" SUN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIR "$N" HIR "悄然遊走至$n" HIR "跟前，陡然使出"
              "三陰手絕技「損筋訣」，單掌輕輕拂過$n" HIR "太陽"
              "穴，不著半點力道。\n" NOR;

        damage = skill / 2 + random(skill / 2);

        ap = me->query_skill("hand");
        dp = target->query_skill("parry");
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -200, me);
                me->start_busy(2);
                target->receive_damage("jing", damage);
                target->receive_wound("jing", damage);
                target->start_busy(1);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK,
                       damage, 50, HIR "$n" HIR "稍不留神，已被$N" HIR
                       "單掌拂中，只覺眼前一黑，幾欲暈倒。\n" NOR);
        }
        else
        {
                addn("neili", -100, me);
                msg += CYN "$n" CYN "見狀大吃一驚，急忙向後猛退數步，"
                       "終于避開了$N" CYN "這一擊。\n" NOR;
                me->start_busy(4);
        }
        message_combatd(msg, me, target);
        return 1;
}