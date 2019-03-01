#include <ansi.h>
#include <combat.h>

#define REN "「" HIW "天地同仁" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int ap, dp, damage;
        string msg;
        object weapon;

        if( userp(me) && !query("can_perform/liangyi-jian/ren", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(REN "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" REN "。\n");

        if ((int)me->query_skill("liangyi-jian", 1) < 120)
                return notify_fail("你兩儀劍法不夠嫻熟，難以施展" REN "。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力修為不足，難以施展" REN "。\n");

        if (me->query_skill_mapped("sword") != "liangyi-jian")
                return notify_fail("你沒有激發兩儀劍法，難以施展" REN "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在真氣不夠，難以施展" REN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "手中長劍劍芒躍動，劍光暴長，劍尖顫動似乎分左右刺向$n"
              HIW "，$n" HIW "看到劍\n光偏左，疾側身右轉，但只這一剎，劍光剎時襲"
              "向右首！\n";

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "sword");

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$n" HIR "疾忙左轉，卻發現$N" HIR
                                           "的" + weapon->name() + HIR "疾往左轉"
                                           "，登時穿胸而過，血如泉湧。\n" NOR);
                addn("neili", -180, me);
        } else
        {
                me->start_busy(3);
                msg += CYN "可是$p" CYN "輕輕一笑，側身右轉，躲開了$P"
                       CYN "左轉的劍式，毫發未傷。\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}