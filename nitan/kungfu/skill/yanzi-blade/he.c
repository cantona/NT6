// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "雙刀合壁" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string type, msg;
        object weapon1, weapon2;
        int i, count, damage;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        weapon1=query_temp("weapon", me);
        weapon2=query_temp("secondary_weapon", me);
        if( !objectp(weapon2) )
        weapon2=query_temp("handing", me);

        if (! objectp(weapon1) || ! objectp(weapon2))
                return notify_fail("你沒有同時裝備雙刀，難以施展" + name() + "。\n");

        if( query("consistence", weapon2) <= 0 )
                return notify_fail("你的" + weapon2->name() + "已經嚴重"
                                   "損壞，無法繼續使用了。\n");

        if( query("skill_type", weapon1) != query("skill_type", weapon2) ||
            query("skill_type", weapon1) != "blade" )
                return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");

        type=query("skill_type", weapon1);

        if (me->query_skill(type, 1) < 250)
                return notify_fail("你的" + to_chinese(type) + "太差，"
                                   "難以施展" + name() + "。\n");

        if (me->query_skill_mapped(type) != "yanzi-blade")
                return notify_fail("你沒有激發燕子雙飛刀法，難以施展" + name() + "。\n");

        if (me->query_skill("yanzi-blade", 1) < 250)
                return notify_fail("你的燕子雙飛刀法等級不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "手持兩把刀，攻向$n " HIW "。可是在這一剎那間，兩把刀仿佛忽然變成了一把刀。\n"
              HIW "雙刀合壁，力量竟增加了一倍，本該是一千斤的力量，竟增加為兩千斤。力量增加了一倍，速度當然也要增加一倍。\n"
              HIW "$N" HIW "雙刀合壁，兩把刀明明已合而為一，卻又偏偏仿佛是從兩個不同的方向劈下來的。\n"
              HIW "明明是砍向$n" HIW "的右邊，可是$n" HIW "往左閃避，還是閃不開。$n" HIW "往右閃，更閃不開。\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap * 2) > dp)
        {
                damage = damage_power(me, "blade") * 2;
                addn("neili", -150, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 85,
                                           HIR "只見$n" HIR "一聲慘叫，胸口給"
                                           "劈開一個巨大的口子，鮮血洶湧噴出！\n" NOR);
                me->start_busy(2);
                if (ap / 3 + random(ap / 2) > dp && ! target->is_busy())
                        target->start_busy(3);
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
