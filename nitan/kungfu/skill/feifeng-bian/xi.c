#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "鳳棲于梧" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i;
        int ap,dp,damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("feifeng-bian", 1) < 120)
                return notify_fail("你的飛鳳鞭法法不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("whip") != "feifeng-bian")
                return notify_fail("你現在沒有激發飛鳳鞭法，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "力貫鞭梢，手中" + weapon->name() + HIW "急舞，畫"
              "出一個又一個的圈子纏向$n" HIW "！\n" NOR;

        ap = attack_power(me, "whip");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "whip");

                addn("neili", -50, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "$n" HIR "只覺得渾身一震，內息有如"
                                           "潮湧，一時不由全身乏力，向後退了一步。\n" NOR);
                msg += HIY "\n$N" HIY "見狀，手中" + weapon->name() + HIY +
                       "急揮，一連數招攻向$n" HIY "！\n" NOR;
                message_combatd(msg, me, target);

                for (i = 0; i < 6; i++)
                {
                        if (! me->is_fighting(target))
                                break;
                        COMBAT_D->do_attack(me, target, weapon, 0);
                }

                me->start_busy(1 + random(4));
        } else
        {
                msg += CYN "可是$p" CYN "輕輕架開$P" CYN
                       "這一招，似乎並沒有廢多少氣力。\n" NOR;
                addn("neili", -70, me);
                me->start_busy(3);
                message_combatd(msg, me, target);
        }

        return 1;
}