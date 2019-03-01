#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("雙劍合璧只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功不夠嫻熟，不能使用雙劍合璧。\n");

        if ((int)me->query_skill("suxin-jian", 1) < 80)
                return notify_fail("你的玉女素心劍不夠嫻熟，不能使用雙劍合璧。\n");

        if ((int)me->query_skill("quanzhen-jian", 1) < 50)
                return notify_fail("你的全真劍法不夠嫻熟，不能使用雙劍合璧。\n");

        if( query("neili", me)<400 )
                return notify_fail("你現在內力太弱，不能使用雙劍合璧。\n");

        if (me->query_skill_mapped("sword") != "suxin-jian")
                return notify_fail("你沒有激發玉女素心劍，不能使用雙劍合璧。\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "左手以全真劍法劍意，右手化玉女劍法劍"
              "招，雙劍合璧同時刺出。\n" NOR;

        if (random(me->query_skill("force")) > target->query_skill("force") / 2)
        {
                me->start_busy(2);

                damage = (int)me->query_skill("sword", 1) +
                         (int)me->query_skill("quanzhen-jian", 1) +
                         (int)me->query_skill("yunv-jian", 1);

                damage = damage / 2 + random(damage / 2);
                addn("neili", -350, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                           HIR "$n" HIR "看到$N" HIR "雙劍飛舞，招式中所有"
                                           "破綻都為另一劍補去，竟不知如何是好！\n"
                                           HIR"一呆之下，$N" HIR "的劍招已經破式而入！$n"
                                           HIR "一聲慘叫之下，登時受了重創！\n" NOR);
        } else
        {
                me->start_busy(3);
                msg += CYN "可是$p" NOR CYN "看破了$P" NOR CYN "的企圖，將"
                       "自己的全身上下護得密不透風，令$P" NOR CYN "無計可施。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
