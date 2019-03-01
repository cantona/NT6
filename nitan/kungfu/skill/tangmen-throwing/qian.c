#include <ansi.h>
#include <combat.h>

string name() { return HIR "心有千千結" NOR; }

#include "/kungfu/skill/eff_msg.h";
inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i, p, n;
        int ap, dp;
        string pmsg;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("handing", me)) ||
            (query("id", weapon) != "qianqian jie" &&
             query("skill_type", weapon) != "throwing") )
                return notify_fail("你現在手中沒有拿著暗器心有千千結，難以施展" + name() + "。\n");

        if ((skill = me->query_skill("tangmen-throwing", 1)) < 140)
                return notify_fail("你的唐門暗器不夠嫻熟，難以施展" + name() + "。\n");

        if( query("tangmen/yanli", me)<80 )
                return notify_fail("你的眼力太差了，目標不精確，無法施展" + name() + "。\n");

        if ((int)me->query_skill("boyun-suowu", 1) < 140)
                return notify_fail("你的撥雲鎖霧不夠嫻熟，無法施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功修為不足，難以施展" + name() + "。\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你現在真氣不足，難以施展" + name() + "。\n");

        if (! living(target) || target->is_busy())
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        addn("neili", -100, me);

        msg = HIR "\n$N" HIR "突然身行一止，從懷中摸出一條" + weapon->name() + HIR "，有無數個結，一揚手向$n " HIR "擲去。\n"
              "只見$n" HIR "的周身飛舞著無數的光影，一條天網從空罩下。\n"NOR;

        ap = attack_power(me, "throwing");
        dp = defense_power(target, "dodge") +
             target->query_skill("dugu-jiujian", 1);

        message_combatd(msg, me, target);
        tell_object(target, HIR "\n你急忙屏氣凝神，希望能夠躲開這致命的" + weapon->name() + HIR "。\n"NOR);
        if (ap / 2 + random(ap) > dp)
        {
                msg = HIR"忽然那無數的光影一閃而沒，$n身行一頓，給這" + weapon->name() + HIR "纏上，仰天而倒。\n" NOR;
                message_combatd(msg, me, target);
                tell_object(target, HIR "你只覺得全身被這" + weapon->name() + HIR "越纏越緊，低頭一看只見那" + weapon->name() + HIR "已經深深的嵌在你的皮肉中。\n" NOR);
                // weapon->hit_ob(me, target, me->query("jiali") + 200);
                if( query("id", weapon) != "qianqian jie" )
                        weapon->add_amount(-1);
                else
                        weapon->move(target);
                target->start_busy(ap / 80 + 2);
        } else
        {
                tell_object(target, HIR "忽然那無數的光影一閃而沒，你心中一驚急忙提神運氣于足間。\n" NOR);
                msg = HIR "$n" HIR "急忙向旁邊一縱，躲開著致命的" + weapon->name() + HIR "，但已顯得狼狽不堪。\n" NOR;
                message_combatd(msg, me, target);
                if( query("neili", target)<1000 )
                        set("neili", 0, target);
                else
                        addn("neili", -1000, target);
                weapon->move(environment(me));
                me->start_busy(3);
        }
        return 1;
}

