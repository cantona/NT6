#include <ansi.h>
#include <combat.h>

#define BAI "「" HIY "朝拜天罡" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int ap, dp, damage;
        string msg;
        object weapon;

        if( userp(me) && !query("can_perform/tiangang-chenfa/bai", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(BAI "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對，難以施展" BAI "。\n");

        if ((int)me->query_skill("tiangang-chenfa", 1) < 120)
                return notify_fail("你天罡塵法不夠嫻熟，難以施展" BAI "。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力修為不足，難以施展" BAI "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在真氣不夠，難以施展" BAI "。\n");

        if (me->query_skill_mapped("whip") != "tiangang-chenfa")
                return notify_fail("你沒有激發天罡塵法，難以施展" BAI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg=HIY"但見$N"HIY"手中"+query("name", weapon)+HIY"竄動不"
              "已，接連變幻了數種招式，分襲$n" HIY "各處要害。\n";

        ap = me->query_skill("whip");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = ap * 4 / 3;
                damage = damage / 2 + random(damage * 2 / 3);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$n" HIR "急忙躲閃，卻發現$N" HIR
                                           "的" + weapon->name() + HIR "已然拂中"
                                           "胸前要穴，頓感氣血上湧，難受之極。\n" NOR);
                addn("neili", -180, me);
        } else
        {
                me->start_busy(3);
                msg += CYN "可是$p" CYN "看破了$P"
                       CYN "招中虛實，當即縱身而起，躲避開來。\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}