// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

string name() { return HIW "參合劍氣" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp, slv, clv,p;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用" + name() + "。\n");

        if (clv = (int)me->query_skill("canhe-zhi", 1) < 180)
                return notify_fail("你的參合指修為有限，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("finger") != "canhe-zhi")
                return notify_fail("你現在沒有準備使用參合指，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 320)
                return notify_fail("你的內功修為太差，難以施展" + name() + "。\n");

        if( query("max_neili", me)<6000 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if( query("neili", me)<900 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        damage = damage_power(me, "finger");
        slv = target->query_skill("six-finger", 1);

        ap = attack_power(me, "finger");
        dp = defense_power(target, "dodge");

        msg = HIW "只見$N" HIW "十指分攤，霎時破空聲驟響，數股劍氣至指尖激"
              "射而出，朝$n" HIW "徑直奔去！\n" NOR;

        if (slv >= 140
            && random(5) == 0
            && slv >= clv - 60 // 如果參合指等級比六脈神劍等級高60級以上取消特殊效果
            &&! target->is_busy()
            && target->query_skill_prepared("finger") == "six-finger")
        {
                msg += HIY "\n但見$n" HIY "斜斜一指點出，指出如風，劍氣縱橫，嗤然"
                       "作響，竟將$N" HIY "的劍氣全部折回，反向自己射去！\n" NOR +
                       HIR "你聽到「嗤啦」一聲輕響，臉上竟濺到一些血滴！\n" NOR;

                me->receive_wound("qi", slv / 3 + random(slv / 4), target);
                p=query("qi", me)*100/query("max_qi", me);
                msg += "( $N" + eff_status_msg(p) + ")\n";

        } else
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 150,
                                           HIR "\n頓時只聽“嗤啦”的一聲，$n" HIR
                                           "躲閃不及，劍氣頓時穿胸而過，帶出一蓬"
                                           "血雨。\n" NOR);
        } else
        {
                msg += CYN "\n$n" CYN "見$N" CYN "來勢洶湧，急忙飛身一躍而"
                       "起，避開了這一擊。\n" NOR;
        }

        ap = attack_power(me, "finger");
        dp = defense_power(target, "force");

        if (slv >= 160
            && random(8) == 0
            && slv >= clv - 60  // 如果參合指等級比六脈神劍等級高60級以上取消特殊效果
            &&! target->is_busy()
            && target->query_skill_prepared("finger") == "six-finger")
        {
                msg += HIY "\n忽見$n" HIY "左手小指一伸，一招「少澤劍」至指尖透出"
                       "，真氣鼓盪，輕靈迅速，頓將$N" HIY "劍氣逼回！\n" NOR + HIR
                       "你聽到「嗤啦」一聲輕響，臉上竟濺到一些血滴！\n" NOR;

                me->receive_wound("qi", slv / 2 + random(slv / 4), target);
                p=query("qi", me)*100/query("max_qi", me);
                msg += "( $N" + eff_status_msg(p) + ")\n";

        } else
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 155,
                                           HIR "\n只聽$n" HIR "一聲慘嚎，被$N" HIR
                                           "的劍氣刺中了要害，血肉模糊，鮮血迸流不"
                                           "止。\n" NOR);
        } else
        {
                msg += CYN "\n$n" CYN "見$N" CYN "來勢洶湧，急忙飛身一躍而"
                       "起，避開了這一擊。\n" NOR;
        }

        ap = attack_power(me, "finger");
        dp = defense_power(target, "parry");

        if (slv >= 180
            && random(10) == 0
            && slv >= clv - 50  // 如果參合指等級比六脈神劍等級高50級以上取消特殊效果
            &&! target->is_busy()
            && target->query_skill_prepared("finger") == "six-finger")
        {
                msg += HIY "\n可電光火石之間，$n" HIY "猛然翻掌，右手陡然探出，中"
                       "指「中沖劍」向$N" HIY "一豎，登將參合劍氣化于無形！\n" NOR
                       + HIR "你聽到「嗤啦」一聲輕響，臉上竟濺到一些血滴！\n" NOR;

                me->receive_wound("qi", slv / 2 + random(slv / 2), target);
                p=query("qi", me)*100/query("max_qi", me);
                msg += "( $N" + eff_status_msg(p) + ")\n";
                me->start_busy(6);

        } else
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 160,
                                           HIR "\n$n" HIR "奮力招架，仍是不敵，$N"
                                           "的" HIR "無形劍氣已透體而入，鮮血飛射"
                                           "，無力再戰。\n" NOR);
        } else
        {
                msg += CYN "\n$n" CYN "見$N" CYN "來勢洶湧，急忙飛身一躍而"
                       "起，避開了這一擊。\n" NOR;
        }
        me->start_busy(3+random(2));
        addn("neili", -400-random(100), me);
        message_combatd(msg, me, target);
        return 1;
}