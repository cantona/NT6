// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "風起雲湧" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if (me->query_skill("dodge", 1) < 140)
                return notify_fail("你的基本輕功的修為不夠，難以施展" + name() + "。\n");

        if (me->query_skill("kuangfeng-jian", 1) < 140)
                return notify_fail("你的狂風快劍修為不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "kuangfeng-jian")
                return notify_fail("你沒有激發狂風快劍，難以施展" + name() + "。\n");

        if( query("neili", me)<250 )
                return notify_fail("你現在真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "凝神聚氣，運轉手中" + weapon->name() + HIW "，剎那間猶如\n"
              "狂風驟起，風聲蕭蕭，" + weapon->name() + HIW "猛地卷向$n" HIW "。\n" NOR;

        ap = attack_power(me, "sword") + me->query_skill("dodge");
        dp = defense_power(target, "parry") + target->query_skill("dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -230, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55 + random(6),
                                           HIR "$n" HIR "看得目瞪口呆，只覺一陣狂風吹過，" + weapon->name() + HIR
                                           "卻已透胸而過。\n" NOR);
        } else
        {
                addn("neili", -120, me);
                me->start_busy(2);
                msg += CYN "可是$n" CYN "微微一笑，輕輕格躲開了$N"
                       CYN "的劍招。\n"NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}
