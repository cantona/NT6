#include <ansi.h>
#include <combat.h>

string name() { return HIR "轉乾坤" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;
        int fmsk;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("tanzhi-shentong", 1) < 220)
                return notify_fail("你的彈指神通不夠嫻熟，難以施展" + name() + "。\n");

        if ((int)me->query_skill("qimen-wuxing", 1) < 200)
                return notify_fail("你的奇門五行修為不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("finger") != "tanzhi-shentong")
                return notify_fail("你沒有激發彈指神通，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("finger") != "tanzhi-shentong")
                return notify_fail("你沒有準備彈指神通，難以施展" + name() + "。\n");

        if( query("max_neili", me)<3500 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if( query("neili", me)<800 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIC "$N" HIC "將全身功力聚于一指，指勁按照二十八宿方位雲貫而出，正"
              "是桃花島「" HIR "轉乾坤" HIC "」絕技。\n" NOR;

        ap = attack_power(me, "finger") + me->query_skill("qimen-wuxing", 1);
        dp = defense_power(target, "dodge") + target->query_skill("qimen-wuxing", 1);
        fmsk = me->query_skill("qimen-xuanshu", 1); 

        if (ap / 2 + random(ap) + fmsk > dp) 
        {
                damage = 0;
                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        me->start_busy(2);
                        msg += HIR "霎那間$n" HIR "只見寒芒一閃，$N" HIR "食指"
                               "已鑽入$p" HIR "印堂半尺，指勁頓時破腦而入。\n"
                               HIW "你聽到“噗”的一聲，身上竟然濺到幾滴腦漿！"
                               "\n" NOR "( $n" RED "受傷過重，已經有如風中殘燭"
                               "，隨時都可能斷氣。" NOR ")\n";
                        message_combatd(msg, me, target); 
                        damage = -1;
                } else
                if (query_temp("thd/tz", me) && random(3) != 1) 
                {
                        damage = damage_power(me, "finger");
                        damage+= query("jiali", me);
                        msg += HIY "\n眼看到$n" HIY "已被點中要穴" 
                               ",$N強提一口真氣，手雙交錯點出，一道道指氣\n"  
                               "頓時將$n逼的退無可退！\n\n" NOR; 
                        
                        for (int i = 0; i < (int)random(9); i++) 
                        {
                                if (! me->is_fighting(target))  
                                        break;  
                                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100, 
                                        HIR "霎那間$n" HIR "只見寒芒一閃，$N" 
                                        HIR "食指已鑽入$p" HIR "胸堂半尺，指勁"  
                                        "頓時破體而入。\n你聽到“嗤”的一聲，"  
                                        "身上竟然濺到幾滴鮮血！\n" NOR); 
                        }
                        message_combatd(msg, me, target); 
                        addn("neili", -300, me);
                        me->start_busy(1 + random(3)); 
                } else
                {
                        me->start_busy(2);
                        damage = damage_power(me, "finger");
                        damage+= query("jiali", me);
                        damage+= fmsk;
                        addn("neili", -500, me);
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 175 + fmsk / 10, 
                                                   HIR "霎那間$n" HIR "只見寒芒一閃，$N"
                                                   HIR "食指已鑽入$p" HIR "胸堂半尺，指勁"
                                                   "頓時破體而入。\n你聽到“嗤”的一聲，"
                                                   "身上竟然濺到幾滴鮮血！\n" NOR);
                        message_combatd(msg, me, target); 
                }
        } else
        {
                me->start_busy(3);
                addn("neili", -300, me);
                msg += CYN "$p" CYN "見$P" CYN "招式奇特，不感大"
                       "意，頓時向後躍數丈，躲閃開來。\n" NOR;
                message_combatd(msg, me, target); 
        }

        if (damage < 0)
        {
                target->receive_damage("qi", 100, me);
                target->die(me);
        }

        return 1;
}
