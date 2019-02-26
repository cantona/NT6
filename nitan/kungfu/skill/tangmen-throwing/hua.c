#include <ansi.h>
#include <combat.h>

string name() { return HIR "唐花" NOR; }

#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i, p, n;
        int ap, dp, damage;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

           if( !objectp(weapon=query_temp("handing", me)) || 
  (query("id", weapon) != "tang hua" &&
           query("skill_type", weapon) != "throwing") )
   return notify_fail("你現在手中沒有拿着暗器唐花，難以施展" + name() + "。\n");

        if ((skill = me->query_skill("tangmen-throwing", 1)) < 180)
                return notify_fail("你的唐門暗器不夠嫻熟，難以施展" + name() + "。\n");

/*
        if( query("tangmen/yanli", me)<80 )
                return notify_fail("你的眼力太差了，目標不精確，無法施展" + name() + "。\n");
*/

        if ((int)me->query_skill("boyun-suowu", 1) < 180)
                return notify_fail("你的撥雲鎖霧不夠嫻熟，無法施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功修為不足，難以施展" + name() + "。\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你現在真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        addn("neili", -100, me);

        msg = HIR "\n$N" HIR "手中突然多了一支花，美得妖豔，$n" HIR "覺得有點痴了，\n$N" HIR "向$n" HIR "一笑，一揚手向$n"HIR "拋去。\n" +
              HIG "只見那花開了，五瓣齊舒，中央花心吐蕊，煞是好看。\n" NOR;

        ap = attack_power(me, "throwing") * 2;
        dp = defense_power(target, "parry") + defense_power(target, "dodge") +
             target->query_skill("dugu-jiujian", 1) * 10;

        message_combatd(msg, me, target);
        tell_object(target, HIC "\n你急忙伸出手去接，但突地，你發現有異，那是一朵鐵花，縱身一躍。\n" NOR);
//        if (ap * 2 / 3 + random(ap * 3 / 2) > dp)
        if (ap / 2 + random(ap) > dp)
        {
                if( query("reborn/times", target) || query("id", weapon) != "tang hua" )
                {
                        string pmsg;

                        weapon->add_amount(-1);
                        damage = damage_power(me, "throwing");
                        damage+= query("jiali", me);
                        msg = HIR "結果$p" HIR "一聲慘嚎，連中了$P" HIR "發出的一" +
                                query("base_unit", weapon)+weapon->name()+HIR"。\n"NOR;

                        COMBAT_D->clear_ahinfo();
                        weapon->hit_ob(me,target,query("jiali", me)+120);

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

                msg = HIR"那花越開越豔，$n" HIR "不知不覺中已痴迷了，身形一慢,微笑着倒下了，那花也謝了。\n" NOR;
                tell_object(target, HIR "\n你看到那花，果真是一朵鐵花。\n你慢慢的伸出手想摘下它，但"
                                        "那花好像變的越來越多了，依稀中你記得那上面有一個小小的“唐”字。\n" NOR);
                weapon->hit_ob(me,target,query("jiali", me)+200);
                weapon->move(target);

                message_combatd(msg, me, target);
                target->receive_wound("qi", 100, me);
                COMBAT_D->clear_ahinfo();
                target->unconcious(me);
                me->start_busy(2);
        } else
        {
                if( query("id", weapon) == "tang hua" )
                        tell_object(target, HIR "果真是唐花，唐門中的唐花。你運足全身的內力，身形掠的更急。\n" NOR);
                msg = HIR "$n " HIR "身形飄忽，那花劃空而過。只聽噹的一聲輕響，那花謝了，輕輕地砸在地面上。\n" NOR;
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

