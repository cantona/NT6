#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "閃刀訣" NOR; }

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
                return notify_fail(name()+"只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對，難以施展"+name()+"。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，難以施展"+name()+"。\n");

        if ((int)me->query_skill("liuhe-dao", 1) < 80)
                return notify_fail("你的六合刀法還不到家，難以施展"+name()+"。\n");

        if (me->query_skill_mapped("blade") != "liuhe-dao")
                return notify_fail("你沒有激發六合刀法，難以施展"+name()+"。\n");

        if( query("neili", me)<150 )
                return notify_fail("你的真氣不夠，難以施展"+name()+"。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "手中的" + weapon->name() +  HIW "吞吐不定，接連"
              "變換了數種方位，最後呼的一聲朝$n" HIW "砍落！\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 35,
                                           HIR "只見$n" HIR "招架不及，頓時被$N"
                                           HIR "這一刀砍中要害，傷口見骨，鮮血狂濺！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += CYN "可是$p" CYN "凝神聚氣，護住門戶，無論$P"
                       CYN "怎樣變招，始終奈何不得。\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}