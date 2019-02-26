//Cracked by Roath
//edit by gladiator 六合連環決

#include <ansi.h>
#include <combat.h>

//inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int skill, lvl, ap, dp, i;
        string msg;
        int damage, hurt, tm;
        
        if( !userp(me) && !query("can_perform/liuhe-bian/lianhuan", me) )
                return notify_fail("你所用的外功中沒有這個功能!\n");
                
        if ( !target ) target = offensive_target(me);

        if ( !target
        ||   !target->is_character()
        ||   !me->is_fighting(target) )
                return notify_fail("六合連環訣只能對戰鬥中的對手使用。\n");

        if( query_temp("lianhuan", me) )
                return notify_fail("你剛剛使用過六合連環訣，內力還未平復！\n");

        weapon=query_temp("weapon", me);

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "whip"
        || me->query_skill_mapped("whip") != "liuhe-bian" ) 
                return notify_fail("你手中無鞭，如何能夠施展連環訣？\n");


        if ( me->query_skill("force") < 270 )
                return notify_fail("你的內功火候未到，無法配合鞭法施展連環訣！\n");

        if ( me->query_skill("whip", 1) < 180 )
                return notify_fail("你鞭發修為不足，還不能使用連環訣！\n");

        if ( me->query_skill("liuhe-bian", 1) < 180 )
                return notify_fail("你六合鞭發修為不足，還不能使用連環訣！\n");

        if( query("neili", me) <= 300 )
                return notify_fail("你的內力不夠施展連環訣！\n");
        
        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");
        if ( me->query_skill("dodge", 1) < 180 )
                return notify_fail("你輕功修為不足，無法快速攻擊！\n");

        skill = me->query_skill("force", 1) + me->query_skill("liuhe-bian", 1) +
                me->query_skill("dodge", 1);
        lvl = me->query_skill("liuhe-bian", 1);
        lvl = lvl / 3;
        
        ap = skill + random(skill);

        dp = target->query_skill("parry", 1) + target->query_skill("dodge", 1);
        
        msg = HIR "\n$N大喝一聲，口中輕輕唸誦佛經，手中" + 
                       weapon->name() + "霍霍，招招連環，"
                       "快如電閃！\n\n" NOR;
        if (random(ap) > dp)
        {    
             i = 6;
             set_temp("lianhuan", 1, me);
             addn_temp("apply/damage", lvl, me);


             tm = 2 + random(2);

             me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), tm);
             addn("neili", -300, me);
                     
             hurt = skill / 2;
             
             damage = hurt / i;
             msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50, 
                    HIY "\n【天合】，$N舞動手中" + weapon->name() + 
                    HIY "瞬息擊向$n的額頭，啪的一聲輕響，頓時一條血印。\n" NOR);
             
             i = 5;
             damage = hurt / i;
             msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50, 
                    HIW "\n【地合】，$N一個橫掃打向$n的下盤，$n未能看破企圖，一聲慘嚎，" 
                    + weapon->name() + HIW "鞭端已沒入小腿半寸" 
                    "，登時連退數步！\n" NOR);
             
             i = 4;
             damage = hurt / i;
             msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50, 
                    HIR "\n【人合】，$N與" + weapon->name() + HIR"合為一體急射向$n，" 
                    "$n措手不急被打的吐血不止！\n" NOR);
             i = 3;
             damage = hurt / i;
             msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50, 
                    HIG "\n【神合】，$N手中" + weapon->name() + HIG "似有靈性一般"
                    "死追着$n而去。\n" NOR);
             i = 2;
             damage = hurt / i;
             msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50, 
                    HIC "\n【鬼合】，$N突然面如死灰，動作僵硬，然後殺氣卻更勝一籌，" 
                    + weapon->name() + HIC "發出靈異的光芒，$n幾乎看到了死亡的顏色。\n" NOR);
        
             i = 1;
             damage = hurt / i;
             msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50, 
                    HIB "\n【六合】，$N口中高唱佛號，手中" + weapon->name() + 
                    HIB "連環擊出，鞭影重重，$n再也支持不住，身上被拉出一條條豁口。\n" NOR);
             
         } else
         {
             msg += CYN "$n" CYN "不慌不忙，以快打快，將$N"
                    CYN "的招式完全化去。\n" NOR;
             addn("neili", -200, me);
             me->start_busy(2 + random(3)); 
         }
        message_combatd(msg, me, target); 
        return 1;
}

void remove_effect(object me, int amount)
{
        int lvl;
        lvl = (int)me->query_skill("liuhe-bian", 1);
        lvl = lvl / 3;
        delete_temp("lianhuan", me);

        if ( me->is_fighting() ) {
                message_vision(HIR "\n$N將內力收回丹田，手上招數也逐漸慢了下來。\n\n" NOR, me);
        }
        else {
                tell_object(me, HIR "\n你的內功運行完畢，將內力緩緩收回丹田。\n\n" NOR);
        }
        addn_temp("apply/damage", -lvl, me);

}
