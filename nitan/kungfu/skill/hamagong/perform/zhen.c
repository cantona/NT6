// This program is a part of NITAN MudLIB
// hama.c 蛤蟆功

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "蟾震九天"; }

#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
        int damage, p, ap, dp;
        string msg, dodge_skill;

        if (! target) target = offensive_target(me);

        if (! target || !target->is_character() ||
            ! me->is_fighting(target) ||
            ! living(target))
                return notify_fail("蟾震九天絕招只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("hamagong", 1) < 100)
                return notify_fail("你的蛤蟆功還不夠熟練，不能使用蟾震九天對敵！\n");

        if( query_temp("weapon", me) )
                return notify_fail("你必須空手才能使用「蟾震九天」！\n");

        if (me->query_skill_mapped("force") != "hamagong")
                return notify_fail("你的內功中無此功夫。\n");

        if (me->query_skill_prepared("strike") != "hamagong" ||
            me->query_skill_mapped("strike") != "hamagong")
                return notify_fail("你必須先將蛤蟆功運用於掌法之中才行。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你現在內力不足，使不出蛤蟆功的絕招蟾震九天！\n");

        if( query("neili", me)<400 )
                return notify_fail("你現在內力不足，使不出蛤蟆功的絕招蟾震九天！\n");

        if ((int)me->query_skill("strike", 1) < 100)
                return notify_fail("你的掌法不夠嫻熟，使不出蛤蟆功的絕招蟾震九天！\n");

        if (me->query_str() < 30 )
                return notify_fail("你的力量太小，使不出用蛤蟆絕招蟾震九天！\n");

        msg = BLU "\n$N身子蹲下，左掌平推而出，使的正是$N生平最得意的「蟾震九天」絕招，掌風直逼$n而去！\n"NOR;

        ap = attack_power(me, "force");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                if (! target->is_busy())
                        target->start_busy(1);

                addn("neili", -200, me);

                damage = damage_power(me, "force");
                if( query("neili", me)>random(query("neili", target)) )
                        damage += query("jiali", me);
                damage *= 2;

                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);

                p=query("eff_qi", target)*100/query("max_qi", target);
                msg += COMBAT_D->damage_msg(damage, "內傷");
                msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
                call_out("perform2", 1, me, target, p, damage);
        } else
        {
                me->start_busy(2);
                if (! target->is_busy())
                        target->start_busy(1);

                addn("neili", -100, me);
                tell_object(target, HIY"你但覺一股微風撲面而來，風勢雖然不勁，然已逼得自己呼吸不暢，知道不妙，連忙躍開數尺。\n" NOR);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }
        message_combatd(msg, me, target);
        return 1;
}

int perform2(object me, object target, int p, int damage)
{
        int ap, dp;
        string msg, dodge_skill;

        if( !target || !me || !living(me)
           || !me->is_fighting(target)
           || environment(target)!=environment(me) || !living(target))
                return 0;

        if( query("neili", me)<500 )
                return notify_fail("你待要再發一掌，卻發現自己的內力不夠了！\n");

        msg = BLU "\n$N左掌勁力未消，右掌也跟着推出，功力相疊，「蟾震九天」掌風排山倒海般湧向$n！\n"NOR;

        ap = attack_power(me, "force");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                if (! target->is_busy())
                        target->start_busy(1);

                addn("neili", -300, me);

                if( query("neili", me)>random(query("neili", target)) )
                        damage += query("jiali", me);
                damage *= 2;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                p=query("qi", target)*100/query("max_qi", target);
                msg += COMBAT_D->damage_msg(damage, "內傷");
                msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
                call_out("perform3", 1, me, target, p, damage);
        }
        else
        {
                me->start_busy(2);
                if (! target->is_busy())
                        target->start_busy(1);
                addn("neili", -200, me);
                tell_object(target, HIY"你喘息未定，又覺一股勁風撲面而來，連忙躍開數尺，狼狽地避開。\n" NOR);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }
        message_vision(msg, me, target);
        return 1;
}

int perform3(object me, object target, int p, int damage)
{
        int ap, dp;
        string msg, dodge_skill;

        if(! target || ! me || environment(me) != environment(target)) return 1;
        if(!living(target))
              return notify_fail("對手已經不能再戰鬥了。\n");

        if( query("neili", me)<700 )
                return notify_fail("你待要再發一掌，卻發現自己的內力不夠了！\n");

        msg = BLU "\n$N雙腿一登，雙掌相併向前猛力推出，$n連同身前方圓三丈全在「蟾震九天」勁力籠罩之下！\n"NOR;

        ap = attack_power(me, "force");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                if (! target->is_busy())
                        target->start_busy(2);

                addn("neili", -400, me);

                if( query("neili", me)>random(query("neili", target)) )
                        damage += query("jiali", me);
                damage *= 2;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                p=query("eff_qi", target)*100/query("max_qi", target);
                msg += COMBAT_D->damage_msg(damage, "瘀傷");
                msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
        } else
        {
                me->start_busy(2);
                if (! target->is_busy())
                        target->start_busy(1);
                addn("neili", -300, me);
                addn("jingli", -100, target);
                tell_object(target, HIY"你用盡全身力量向右一縱一滾，搖搖欲倒地站了起來，但總算躲開了這致命的一擊！\n" NOR);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }

        message_combatd(msg, me, target);
        return 1;
}
