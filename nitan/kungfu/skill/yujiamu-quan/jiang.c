// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "修羅降世" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int angry;
        string msg;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        skill = me->query_skill("yujiamu-quan", 1);

        if (skill < 100)
                return notify_fail("你金剛瑜迦母拳修為不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("cuff") != "yujiamu-quan")
                return notify_fail("你沒有激發金剛瑜迦母拳，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("cuff") != "yujiamu-quan")
                return notify_fail("你沒有準備金剛瑜迦母拳，難以施展" + name() + "。\n");

        if( query("neili", me)<180 )
                return notify_fail("你目前的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        if( angry=query("qi", me)<query("max_qi", me)/2 )
                msg = HIR "$N" HIR "目睚俱裂，一聲爆喝，全身骨骼劈啪作響，拳"
                      "頭如閃電般擊向$n" HIR "的要害！\n" NOR;
        else
                msg = HIR "$N" HIR "大喝一聲，面色赤紅，全身骨骼劈啪作響，拳"
                      "頭如閃電般擊向$n" HIR "的要害！\n" NOR;

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -100, me);
                me->start_busy(1);
                damage = damage_power(me, "cuff");
                if (angry) damage += random(damage / 2);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45,
                                           HIR "結果$p" HIR "無法抵擋$P" HIR "這雷"
                                           "霆一擊，登時被打退數步，搖晃不定。\n" NOR);
        } else
        {
                addn("neili", -40, me);
                msg += CYN "可是$p" CYN "並未被這氣勢所懾，輕移"
                       "腳步，躲開了$P" CYN "的攻擊。\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}