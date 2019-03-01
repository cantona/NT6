#include <ansi.h>
#include <combat.h>

string name() { return HIY "當時明月在" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 160)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("moon-blade", 1) < 120)
                return notify_fail("你的圓月彎刀還不到家，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "moon-blade")
                return notify_fail("你沒有激發圓月彎刀，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "刀氣橫空，刀光爍閃，連環七刀，每刀均令$n" HIY "不得不全神應付，\n"
              "每刀均是樸實古拙，偏又有，明月當空的感覺。\n"
              "且刀刀均針對$n" HIY "的身形變化，似是把$n" HIY "看通看透一般！\n" NOR;

        ap = attack_power(me, "blade") + me->query_skill("force", 1);
        dp = defense_power(target, "force") + target->query_skill("force", 1);

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                damage+= query("jiali", me);
                damage *= 3;
                addn("neili", -150, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 600,
                                           HIR "霎時一股冰寒的刀氣掠過全身，$n"
                                           HIR "全身頓時鮮血淋漓，搖搖欲倒！\n" NOR);
                me->start_busy(2);
                if (ap / 2 + random(ap * 2) > dp && ! target->is_busy())
                        target->start_busy(ap / 80 + 3);
        } else
        {
                msg += CYN "$p" CYN "大吃一驚，也不招架，當即向後"
                       "橫移數尺，避開了$P" CYN "這一招。\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

