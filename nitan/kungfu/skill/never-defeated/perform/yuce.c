// yuce.c

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        int skill, i;
        int n, damage;
        int my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("御策訣只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
            query("skill_type", weapon) != "throwing" || 
            weapon->query_amount() < 1)
                return notify_fail("你現在手中並沒有拿著暗器，怎麼施展御策訣？\n");

        if ((skill = me->query_skill("never-defeated", 1)) < 100)
                return notify_fail("你的不敗神功火候不夠，不會施展御策訣。\n");

        if( query("neili", me)<150 )
                return notify_fail("你內力不夠了。\n");

        if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        addn("neili", -120, me);
        weapon->add_amount(-1);

        msg = HIC "$N" HIC "手指一合一彈，只聽呼嘯破空聲起，有若龍吟，一" +
             query("base_unit", weapon)+weapon->name()+HIC"如蛟龍般"+
             "打向$n" HIC "。\n" NOR;

        me->start_busy(1);
        my_exp = attack_power(me, "throwing");
        ob_exp = defense_power(target, "parry");
        if (my_exp / 2 + random(my_exp) > ob_exp)
        {
                msg += HIR + "只見那" + weapon->name() + HIR "去勢恰如神光閃電！$n"
                       HIR + "不及閃避，被打了個正中，慘叫一"
                       "聲，退了幾步。\n" NOR;
                       
                damage = damage_power(me, "throwing") * 3 / 2;
                target->receive_wound("qi", damage, me);
                COMBAT_D->clear_ahinfo();
                weapon->hit_ob(me, target,
                               query("jiali", me)+150);
                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;
                message_combatd(msg, me, target);
        } else
        {
                msg += CYN "可是$p" CYN "急忙一閃，躲過了$P" HIG "發出的" +
                       weapon->name() + CYN "。\n" NOR;
                message_combatd(msg, me, target);
        }

        me->reset_action();
        return 1;
}