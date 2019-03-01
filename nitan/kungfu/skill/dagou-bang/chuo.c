// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "戳字訣" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage, level;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        level = me->query_skill("dagou-bang", 1);

        if (level < 100)
                return notify_fail("你打狗棒法不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("staff") != "dagou-bang")
                return notify_fail("你沒有激發打狗棒法，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 160)
                return notify_fail("你的內功火候不足，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIG "$N" HIG "使出打狗棒法「" HIR "戳" HIG "」字訣，單"
              "手一振，霎時棒影竄動，疾刺$n" HIG "胸前要穴。\n" NOR;

        ap = attack_power(me, "staff");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "staff");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "$n" HIR "全然無法勘破$N" HIR "的"
                                           "精妙招式，胸口一麻，射出一柱鮮血！\n" NOR);
                me->start_busy(2);
                addn("neili", -100, me);
        } else
        {
                msg += CYN "可$n" CYN "全神防御，不露半點破綻，使得$N"
                       CYN "這招無功而返。\n" NOR;
                me->start_busy(3);
                addn("neili", -50, me);
        }
        message_combatd(msg, me, target);

        return 1;
}
