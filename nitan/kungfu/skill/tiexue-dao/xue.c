#include <ansi.h>
#include <combat.h>

string name() { return HIR "血浪滔天" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "blade" )
                return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");

        if (me->query_skill("tiexue-dao", 1) < 100)
                return notify_fail("你鐵血刀法等級不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "tiexue-dao")
                return notify_fail("你沒有激發鐵血刀法，難以施展" + name() + "。\n");

        if (me->query_skill("force") < 150)
                return notify_fail("你的內功修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你目前的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIR "$N" HIR "殺氣大盛，手中" + weapon->name() +
              HIR "一振，頓時一道血光從刀鋒閃過，將$n"
              HIR "團團裹住。\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 35,
                                           HIR "只聽$n" HIR "一聲慘嚎，嗤啦一聲，"
                                           "一股血柱自" HIR "血色刀影中激射而出。"
                                           "\n" NOR);
                me->start_busy(2);
                addn("neili", -120, me);
        } else
        {
                msg += CYN "可是$n" CYN "眼明手快，奮力招架，將$N"
                       CYN "的招式全部擋開。\n" NOR;
                me->start_busy(3);
                addn("neili", -80, me);
        }
        message_combatd(msg, me, target);

        return 1;
}