#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "碧焰滔天" NOR; }

int unconcious_me(object me);

int perform(object me, object target)
{
        object du;
        int damage;
        string msg, msg1;
        int ap, dp, lvl;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("你只能對戰鬥中的對手施展" + name() + "。\n");

        if ((int)me->query_skill("chousui-zhang", 1) < 220)
                return notify_fail("你的抽髓掌火候不夠。\n");

        if ((int)me->query_skill("poison", 1) < 250)
                return notify_fail("你的基本毒技火候不夠。\n");

        if ((int)me->query_skill("huagong-dafa", 1) < 220)
                return notify_fail("你的化功大法火候不夠。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的內力修為不足，無法用內力施展" + name() + "。\n");

        if( query("neili", me)<3000 )
                return notify_fail("你現在內息不足，無法用內力施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "chousui-zhang")
                return notify_fail("你還沒有準備抽髓掌，無法施展" + name() + "。\n");

        /*
        if( !query_temp("powerup", me) )
                return notify_fail("你必須將全身功力盡數提起才能施展" + name() + "。\n");

        if( !objectp(du=query_temp("handing", me)) && userp(me) )
                return notify_fail("你首先要拿着(hand)一些毒藥作為引子。\n");

        if( query("poison", objectp(du) && !mapp(du)) )
                return notify_fail(du->name() + "又不是毒藥，無法運射出毒焰？\n");
        */

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIR "只見$N" HIR "雙目血紅，頭髮散亂，猛地仰天發出一聲悲嘯。\n\n"
              "$N" HIR "把心一橫，在自己舌尖狠命一咬，將畢生功力盡"
              "數噴出，頓時只見空氣中血霧瀰漫，腥臭無比，隨即又\n"
              "聽$N" HIR "骨骼“噼裏啪啦”一陣爆響，雙臂順着噴出的"
              "血柱一推，剎那間一座丈來高的奇毒火牆拔地而起，帶\n"
              "着排山倒海之勢向$n" HIR "湧去！\n" NOR;
        me->start_busy(2 + random(2));
        addn("neili", -1000, me);

        lvl = me->query_skill("chousui-zhang", 1);
        damage = damage_power(me, "strike");
        damage+= query("jiali", me);

        /*
        if (lvl / 2 + random(lvl) < target->query_skill("force", 1))
        {
                if( query("max_neili", me)+random(query("max_neili", me))<
                    query("max_neili", target)*18/10 )
                {
                        msg += WHT "$n" WHT "見狀連忙提運內力，雙臂猛"
                                "的推出，掌風澎湃，強大的氣流頓時將火浪"
                                "颳得倒轉，竟然掉頭向$N" WHT "撲去。\n\n" NOR;
                        msg += HIR "$N" HIR "一聲慘笑，長歎一聲，眼前一黑，倒在了地上。\n\n" NOR;
                        //me->addn("max_neili", -random(50));
                        me->receive_damage("qi", 1, target);

                        remove_call_out("unconcious_me");
                        call_out("unconcious_me", 1, me);

                }
        } else
        {
        */
                ap = attack_power(me, "strike") +
                     me->query_skill("poison", 1);
                dp = defense_power(target, "dodge") +
                     target->query_skill("force", 1)/2;

                if (ap + random(ap) < dp)
                {
                        msg += CYN "$n" CYN "見勢不妙，急忙騰挪身形，避開了$N" CYN "的攻擊。\n" NOR;
                        // me->addn("max_neili", -random(50));
                        if (! target->is_busy())
                                target->start_busy(3);
                } else
                {
                        msg1 = HIR "$n" HIR "見滔天熱浪撲面湧來，只覺眼前一片通紅，"
                               "已被捲入火浪，毒焰席捲全身，連骨頭都要烤焦一般。\n" NOR;
                        // me->addn("max_neili", -random(50));
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 90, msg1);

                        target->affect_by("fire_poison",
                                       (["level":query("jiali", me)*6+random(query("jiali", me)*4),
                                          "id":query("id", me),
                                          "duration" : lvl / 20 + random(lvl) ]));

                        target->receive_damage("qi", damage * 2);
                        target->receive_damage("jing", damage);
                        if (! target->is_busy())
                                target->start_busy(5);
                }
        /*
        }

        if (objectp(du)) destruct(du);
        */
        message_vision(msg, me, target);
        /*
        me->want_kill(target);
        if (! target->is_killing(me)) target->kill_ob(me);
        */
        return 1;
}

int unconcious_me(object me)
{
        if (! objectp(me))
              return 1;

        if (living(me))
              me->unconcious();

        return 1;
}