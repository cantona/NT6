#include <ansi.h>
#include <combat.h>

string name() { return HIR "鬼影奪目" NOR; }

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int lvl, ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        weapon=query_temp("weapon", me);

        if( weapon && query("skill_type", weapon) != "sword"
            && query("skill_type", weapon) != "pin" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("pixie-jian", 1) < 80)
                return notify_fail("你的辟邪劍法不夠嫻熟，難以施展" + name() + "。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (weapon && me->query_skill_mapped("sword") != "pixie-jian")
                return notify_fail("你沒有準備使用辟邪劍法，難以施展" + name() + "。\n");

        if (! weapon && me->query_skill_prepared("unarmed") != "pixie-jian")
                return notify_fail("你沒有準備使用辟邪劍法，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        if( query_temp("block_msg/all", target) )
                return notify_fail("對方現在什麼也看不見，放膽攻擊吧。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
        {
                msg = HIR "$N" HIR "一聲陰笑，揉身而上，左手兩指並攏，手臂"
                      "暴長，迅捷異常分刺$n" HIR "的雙目！\n" NOR;
        } else
        {
                msg = HIR "$N" HIR "一聲陰笑，揉身而上，手中" + weapon->name() +
                      HIR "一振，劍尖一點暴長，分刺$n" HIR "左右雙目！\n" NOR;
        }

        ap = attack_power(me, "sword") +
             me->query_skill("dodge");

        dp = defense_power(target, "parry") +
             target->query_skill("dodge");

        if (ap / 2 + random(ap*2) > dp)
        {
                damage = damage_power(me, "sword");

                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 65,
                                          (: final, me, target, me->query_skill("pixie-jian", 1) :));
                me->start_busy(2);
                addn("neili", -80, me);
                message_combatd(msg, me, target);
                set_temp("block_msg/all", 1, target);
        } else
        {
                msg += CYN "$n" CYN "情急智生，抬手也向$N"
                       CYN "的右眼刺去，迫得$P" CYN "回劍躍開。\n" NOR;
                me->start_busy(3);
                addn("neili", -50, me);
                message_combatd(msg, me, target);
        }
        return 1;
}

string final(object me, object target, int ap)
{
        target->start_call_out((: call_other, __FILE__, "cimu_end", me, target :), 5 + random(ap / 100));
        return HIR "$n" HIR "只覺雙目一陣劇痛，眼前一黑，就什麼"
               "也看不見了，頓時長聲痛極而呼。\n" NOR;
}

void cimu_end(object me, object target)
{
        if (! objectp(target)) return;
        if( target && query_temp("block_msg/all", target) )
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "抹了抹流著的"
                                        HIR "鮮血" HIC "，終于能看"
                                        "見了。\n" NOR, target);

                        tell_object(target, HIR "你終于抹掉了眼前的"
                                            "鮮血，能看見了。\n" NOR);
                        set_temp("block_msg/all", 0, target);
                }
        }
        return;
}