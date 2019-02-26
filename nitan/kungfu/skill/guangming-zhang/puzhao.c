// 聖火普照

#include <ansi.h>

inherit F_SSERVER;

string name() { return "聖火普照"; }

int perform(object me, object target)
{
        int damage;
        int ap,dp;
        string msg,str;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("你只能對戰鬥中的對手施展聖火普照。\n");

        if (query_temp("weapon", me))
                return notify_fail("你只有空手才能使用光明神掌。\n");

        if (!(me->query_skill_mapped("strike") == "guangming-zhang"))
                return notify_fail("你並沒有激發光明神掌，如何用聖火普照？\n");

        if (!(me->query_skill_prepared("strike") == "guangming-zhang"))
                return notify_fail("你並沒有準備光明神掌，如何用聖火普照？\n");

        if ((int)me->query_skill("guangming-zhang", 1) < 80)
                return notify_fail("你的光明神掌火候不夠。\n");

        if ((int)query("max_neili", me) < 500)
                return notify_fail("你的內力修為不足，無法用內力施展聖火普照。\n");

        if ((int)query("neili", me) < 200)
                return notify_fail("你現在內息不足，無法用內力施展聖火普照      。\n");

        msg = HIR "只見$N" HIR "面色端莊，無喜無怒，無慈無悲，口中喃喃不絕，渾身紅光大盛！\n\n"
              "$N" HIR "雙掌緩緩抬起，兩團耀眼的血色光芒籠罩着手掌，看起來詭異絕倫！\n\n"
              "猛然間，$N" HIR "吐氣長嘯，雙掌迅猛推出，紅色光芒帶着滾滾熱浪將$n整個包圍起來！\n\n"NOR;

        me->start_busy(1 + random(2));
        addn("neili", -50, me);


        damage = damage_power(me, "strike");

        ap = attack_power(me, "strike") + me->query_str()*10;
        ap = defense_power(target, "dodge") + target->query_dex()*10;

        if (ap < dp)
        {
                msg += HIY "$n" HIY "屏氣凝神，不受滿眼紅芒的困擾"
                       "，身形急閃，掙脱了$N" HIY "這烈焰滔天的可怕一掌。\n\n";
        } else
        {
                msg += HIR "$n" HIR "只覺得眼前紅光一片，再也看不到$N的身形，"
                               "大驚失色下，火浪已經席捲而止，接着胸口給重重印上一掌，不由鮮血狂噴！\n\n" NOR;
                        target->receive_damage("qi", damage, me );
                        target->receive_wound("qi", random(damage/2), me);
                        if (! target->is_busy())
                        target->start_busy(2);
                        str = COMBAT_D->status_msg((int)query("qi", target) * 100 /(int)query("max_qi", target));
                        msg += "($n"+str+")\n";
        }

        message_combatd(msg, me, target);
        //me->want_kill(target);
        //if (! target->is_killing(me)) target->kill_ob(me);
        return 1;
}