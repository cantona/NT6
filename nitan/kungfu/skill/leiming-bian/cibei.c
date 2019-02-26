#include <ansi.h>
#include <combat.h> 

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
        string msg, dodge_skill;
        int extra, skill, at, df, i, lmt, damage, p;
        object weapon;
        extra = me->query_skill("leiming-bian",1);

        if( userp(me) && !query("can_perform/leiming-bian/cibei", me) )
              return notify_fail("你使用的外功中沒有這個功能。\n");
        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
              return notify_fail("［慈悲字訣］只能對戰鬥中的對手使用。\n");

        if( extra < 160)
              return notify_fail("你的雷鳴鞭法修為太差,還不能使用慈悲字訣！\n");

        skill = me->query_skill("buddhism", 1);

        if( skill < 150)
              return notify_fail("你的禪宗心法等級不夠，怎能支持慈悲字訣？ \n");

        if( query("shen", me)<200000 )
              return notify_fail("慈悲字訣需以無邊正氣為輔,大師還是多行善事吧! \n");

        if( query("neili", me)<1500 )
              return notify_fail("你的內力修為不夠輔助慈悲字訣。\n");

        weapon=query_temp("weapon", me);

        if( !weapon
          || query("skill_type", weapon) != "whip" )
              return notify_fail("你手中沒有兵器如何使用慈悲字訣。\n");

        msg = RED "只見$N喃喃自語道：慈悲為懷，手中的" + weapon->name() + RED "彷彿如來出世般倒卷向$n。\n" NOR;
        
        at=query("combat_exp")*me->query_skill("leiming-bian", me)/1000;
        df=query("combat_exp")*target->query_skill("dodge", target)/1000;
        
        if( (random(at) + at / 2)  > df )
        {
            damage=query("shen", me)/2000;
            
            if(damage > 1500) damage = 1500 + (damage-1500)/100;
            
            msg += CYN "$n不禁被$N的無邊佛法打動，猛的後退，臉上沒有一絲血色...\n" NOR;
            target->receive_damage("qi", damage, me);
            target->receive_wound("qi", damage / 3, me);
            
            p=query("qi", target)*100/query("max_qi", target);
            msg += "( $n" + eff_status_msg(p) + " )\n"; 
            message_vision(msg, me, target);
            target->start_busy(3);
            
            weapon=query_temp("weapon", me);
            msg = HIG "\n緊接着$N手中的" + weapon->name() + HIG "連續晃動，竟然不知道有多少擊。\n" NOR;
            message_vision(msg,me,target);
            
            lmt = random(me->query_skill("leiming-bian", 1) / 50) + 1;
            if ( lmt < 3 ) lmt = 3;
            if ( lmt > 6 ) lmt = 6;

            for(i=1;i <= lmt;i++)
            {
                 extra = me->query_skill("leiming-bian", 1);
                 addn_temp("apply/attack", extra/5, me);
                 addn_temp("apply/damage", extra/5, me);
                 COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);
                 addn_temp("apply/attack", -extra/5, me);
                 addn_temp("apply/damage", -extra/5, me);
            }
            addn("neili", -300, me);
            me->start_busy(random(2) + 2);
        } else 
       {      
              msg = HIG "\n$n左躲右閃，強$N的攻擊完全化於無形！\n" NOR;
              message_vision(msg,me,target);
              addn("neili", -200, me);
              me->start_busy(random(2));
       }
        return 1;
}
