#include <ansi.h>
#include <combat.h>

string name() { return HIR "七子剛鏢" NOR; }

#include "/kungfu/skill/eff_msg.h";
inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i, p, n;
        int ap, dp, damage;
        string pmsg;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("handing", me)) ||
            (query("id", weapon) != "qizi gangbiao" &&
             query("skill_type", weapon) != "throwing") )
                return notify_fail("你現在手中沒有拿著暗器七子剛鏢，難以施展" + name() + "。\n");

        if( query("id", weapon) != "qizi gangbiao" &&
             weapon->query_amount() < 7)
                return notify_fail("你現在手中沒有足夠的暗器，難以施展" + name() + "。\n");

        if ((skill = me->query_skill("tangmen-throwing", 1)) < 120)
                return notify_fail("你的唐門暗器不夠嫻熟，難以施展" + name() + "。\n");

        if( query("tangmen/yanli", me)<80 )
                return notify_fail("你的眼力太差了，目標不精確，無法施展" + name() + "。\n");

        if ((int)me->query_skill("boyun-suowu", 1) < 120)
                return notify_fail("你的撥雲鎖霧不夠嫻熟，無法施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功修為不足，難以施展" + name() + "。\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你現在真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        addn("neili", -100, me);

        msg = HIR "\n$N" HIR "突然身行一止，從懷中摸出七枚手掌大小的" + weapon->name() + HIR "，一揚手向$n " HIR "擲去。\n"
              "只見七枚" + weapon->name() + HIR "，飛旋打出，$n" HIR "的周身飛舞著無數的光影，卻聽不到一絲聲音。\n"NOR;

        ap = attack_power(me, "throwing");
        dp = defense_power(target, "parry") +
             target->query_skill("dugu-jiujian", 1);

        message_combatd(msg, me, target);
        tell_object(target, HIR "\n你急忙屏氣凝神，希望能夠招架這致命的一擊。\n"NOR);
        if (ap / 2 + random(ap) > dp)
        {
                if( query("id", weapon) != "qizi gangbiao" )
                {
                        n = 7;
                        weapon->add_amount(-7);
                        damage = damage_power(me, "throwing");
                        damage+= query("jiali", me);
                        msg = HIR "結果$p" HIR "一聲慘嚎，連中了$P" HIR "發出的七" +
                                query("base_unit", weapon)+weapon->name()+HIR"。\n"NOR;

                        while (n--)
                        {
                                COMBAT_D->clear_ahinfo();
                                weapon->hit_ob(me, target,
                                               query("jiali", me)+100+n*10);
                        }

                        target->receive_damage("qi", damage, me);
                        target->receive_wound("qi", damage, me);

                        p=query("qi", target)*100/query("max_qi", target);

                        if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                                msg += pmsg;

                        msg += "( $n" + eff_status_msg(p) + " )\n";
                        message_combatd(msg, me, target);
                        me->start_busy(2);
                        return 1;
                }
                msg = HIR "忽然那無數的光影一閃而沒，$n身行一頓，噴出一口鮮血，仰天而倒。\n" NOR;
                message_combatd(msg, me, target);
                tell_object(target, HIR "你只覺得胸口一陣鑽心的疼痛。低頭一看只見那七枚暗器已經深深的嵌在你的心口。\n"
                                    "血跡中隱約有幾個小字[七子剛鏢...]。\n"NOR);
                weapon->hit_ob(me,target,query("jiali", me)+200);
                weapon->move(target);


                target->receive_wound("qi", 100, me);
                COMBAT_D->clear_ahinfo();
                target->unconcious(me);
                me->start_busy(2);
        } else
        {
                tell_object(target, HIR "忽然那無數的光影一閃而沒，你心中一驚急忙運內力于全身。\n" NOR);
                msg = HIR "$n" HIR "雙臂急舞，衣袖帶起破風之聲。只聽當的一聲輕響，竟將那七枚暗器磕飛開去。\n" NOR;
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

