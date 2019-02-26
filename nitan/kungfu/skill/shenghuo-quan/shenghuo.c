// 聖火焚軀

#include <ansi.h>

inherit F_SSERVER;

string name() { return "聖火焚軀"; }

int perform(object me, object target)
{
        int damage;
        int ap,dp;
        string msg,str;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("你只能對戰鬥中的對手施展聖火焚軀。\n");

        if (query_temp("weapon", me))
                return notify_fail("你只有空手才能使用聖火拳。\n");

        if (!(me->query_skill_mapped("cuff") == "shenghuo-quan"))
                return notify_fail("你並沒有激發聖火拳，如何用聖火焚軀？\n");

        if (!(me->query_skill_prepared("cuff") == "shenghuo-quan"))
                return notify_fail("你並沒有準備聖火拳，如何用聖火焚軀？\n");

        if ((int)me->query_skill("shenghuo-quan", 1) < 60)
                return notify_fail("你的聖火拳火候不夠。\n");

        if ((int)query("max_neili", me) < 200)
                return notify_fail("你的內力修為不足，無法用內力施展聖火焚軀。\n");

        if ((int)query("neili", me) < 100)
                return notify_fail("你現在內息不足，無法用內力施展聖火焚軀。\n");

        msg = HIR "只見$N" HIR "一聲呼嘯，面臉突顯一片紅光，雙拳收於胸口，頃刻從肩膀到拳頭都成為赤色。\n\n"
              "$N" HIR "深吸一口氣，雙拳閃電般飛出，滾滾熱浪衝$n" HIR "飛卷而去，令人感到一陣窒息。\n\n"NOR;

        me->start_busy(1 + random(2));
        addn("neili", -50, me);

        damage = damage_power(me, "cuff");

        ap = attack_power(me, "cuff") + me->query_str();
        dp = defense_power(target, "dodge") + target->query_dex();

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIR "$n" HIR "見炙熱拳風撲面湧來，只覺渾身一陣劇痛，"
                               "已被捲入猛烈的拳勁，烈火席捲全身，不由悶哼一聲。\n\n" NOR;
                        target->receive_damage("qi", damage, me );
                        target->receive_wound("qi", random(damage/2), me);
                        target->start_busy(2);
                        str = COMBAT_D->status_msg((int)query("qi", target) * 100 /(int)query("max_qi", target));
                        msg += "($n"+str+")\n";
        } else
        {
                msg += HIY "$n" HIY "見狀連忙提運內力，雙足點地"
                       "，身形急退，避開了$N" HIY "撲面而來的炙熱拳風。\n\n";
        }

        message_combatd(msg, me, target);
        //me->want_kill(target);
        //if (! target->is_killing(me)) target->kill_ob(me);
        return 1;
}