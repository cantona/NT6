#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "驚天一劍" NOR; }

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
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("duanjia-jian", 1) < 80)
                return notify_fail("你的段家劍法不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "duanjia-jian")
                return notify_fail("你現在沒有激發段家劍，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的內功修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIR "$N" HIR "一躍而起，手腕一抖，挽出一個美麗的劍花，飛向$n"
              HIR "而去。\n"NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -150, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIR "只見$N" HIR "人劍合一，穿向$n"
                                           HIR "，$n" HIR "只覺一股熱流穿心而"
                                           "過，喉頭一甜，鮮血狂噴而出！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += CYN "可是$p" CYN "猛地向邊上一躍，跳出了$P"
                       CYN "的攻擊範圍。\n"NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
