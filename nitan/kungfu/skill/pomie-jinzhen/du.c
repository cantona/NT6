#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return YEL "金針渡劫" NOR; }

#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
        int skill, i, p;
        int n;
        int my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("handing", me) )
            || query("skill_type", weapon) != "throwing" )
                return notify_fail("你現在手中並沒有拿着暗器。\n");

        if (weapon->query_amount() < 30)
                return notify_fail("你至少要拿有二十枚暗器才能施展" + name() + "。\n");

        if ((skill = me->query_skill("pomie-jinzhen", 1)) < 150)
                return notify_fail("你的破滅金針不夠嫻熟，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = YEL "只見$N" YEL "右手一揚，施出「" HIR "金針渡劫" NOR +
              YEL "」，手中" + weapon->name() + YEL "如急風暴雨般向$n"
              YEL "射去！\n" NOR;

        my_exp=attack_power(me, "throwing");
        ob_exp=defense_power(target, "dodge");

        if (my_exp / 2 + random(my_exp) > ob_exp)
        {
                n = 4 + random(4);
                if (random(my_exp) > ob_exp) n += 4 + random(4);
                if (random(my_exp / 2) > ob_exp) n += 4 + random(4);
                if (random(my_exp / 4) > ob_exp) n += 4 + random(8);
                if (weapon->query_amount() < n) n = weapon->query_amount();

                msg += HIR "霎時間一片金芒籠罩$n" HIR "四方，聽得一聲"
                       "慘叫，" + chinese_number(n) + "柱鮮血飛濺而出"
                       "。\n" NOR;

                target->receive_damage("qi", skill + random(skill), me);
                target->receive_wound("qi", skill / 2 + random(skill / 2), me);
                p=query("qi", target)*100/query("max_qi", target);
                while (n--)
                {
                        COMBAT_D->clear_ahinfo();
                        weapon->hit_ob(me,target,query("jiali", me)*2+300+n*15);
                }
                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;
                        msg += "( $n" + eff_status_msg(p) + " )\n";
                message_combatd(msg, me, target);
        } else
        {
                msg += CYN "可是$n" CYN "絲毫不敢大意，當即左閃右"
                       "避，躲開了所有的暗器。\n" NOR;
                message_combatd(msg, me, target);
        }
        weapon->set_amount(0);
        addn("neili", -100, me);
        me->start_busy(2);
        me->reset_action();
        return 1;
}