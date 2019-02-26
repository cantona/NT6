// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "先天罡氣" NOR; }

inherit F_SSERVER;

string attack1(object me, object target, int damage);
string attack2(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");
        
        if( !query("reborn/times", me) )
                return notify_fail("你尚未轉世重生，無法使用" + name() + "。\n"); 

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("xiantian-gong", 1) < 1000)
                return notify_fail("你的先天功修為不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "xiantian-gong")
                return notify_fail("你沒有激發先天功為拳腳，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("你沒有激發先天功為內功，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "xiantian-gong")
                return notify_fail("你沒有準備使用先天功，難以施展" + name() + "。\n");

        if( query("neili", me)<2000 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "\n$N" HIW "施出先天罡氣，頓時將方圓十里天地之氣吸入體內"
              "，凝聚於雙手手掌處，左手一揮，層層疊疊湧向$n" HIW "！\n" NOR;

        addn_temp("apply/ap_power", 30, me);
        ap=attack_power(me,"unarmed")+me->query_con()*20;
        dp=defense_power(target,"parry")+target->query_dex()*20;
        
        damage = damage_power(me, "unarmed");
        damage+= query("jiali", me);
        damage *= 3;
        
        if (ap / 2 + random(ap) > dp)
        {
                if( !target->is_busy() )
                        target->start_busy(2);
                
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
                                                    (: attack1, me, target, damage :));
        } else
        {
                msg += CYN "$n" CYN "倒吸一口涼氣，飛身一跳，狼狽地躲過這招。\n" NOR; 
        }
        
        message_combatd(msg, me, target); 
        msg = HIW "緊接着，$N" HIW "一聲清嘯，右手虛向$n"HIW"蓋下，龐大的天地之氣洶湧般壓向$n" HIW "！\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                if( !target->is_busy() )
                        target->start_busy(2);
                        
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 500,
                                                   (: attack2, me, target, damage :));
        } else
        {
                msg += CYN "$n" CYN "倒吸一口涼氣，飛身一跳，狼狽地躲過這招。\n" NOR; 
        }
        
        message_combatd(msg, me, target);
        addn_temp("apply/ap_power", -30, me);
        addn("neili", -1000, me);
       
        me->start_busy(3 + random(2));

        return 1;
}

string attack1(object me, object target, int damage)
{
        string msg;

        target->receive_damage("jing", damage);
        target->receive_wound("jing", damage / 2);
                
        msg = HIR "結果$N" HIR "這掌正中$n" HIR "胸"
              "口，先天罡氣登時貫腦而入，接連噴出數"
              "口鮮血。\n" NOR;
        
        //if (random(2) != 1) return msg;

        set("neili", 0, target);

        msg += WHT "$n" WHT "只感到胸口一痛，全身真氣宛若遊絲，難受無比。\n" NOR;

        return msg;
}

void clear_no_exert(object target)
{
        if( !objectp(target) ) return;

        target->clear_condition("no_exert");
}

string attack2(object me, object target, int damage)
{
        string msg;

        msg = HIR "結果$N" HIR "這掌正中$n" HIR "胸"
              "口，先天罡氣登時貫體而入，接連噴出數"
              "口鮮血。\n" NOR;

        //if (random(2) != 1) return msg;
        //if( target->query_condition("no_exert") ) return msg;

        target->apply_condition("no_exert", 10);
        call_out("clear_no_exert", 25, target);
        
        msg += WHT "$n" WHT "感到氣脈受損，內息紊亂，説不出的痛苦。\n" NOR;

        return msg;
}
