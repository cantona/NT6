// xuan.c
// modify by xiha@wmkj

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>


inherit F_SSERVER;
int get_current_day_phase();
nosave mapping *day_phase = NATURE_D->query_day_phase(); 

int perform(object me, object target)
{
        object weapon, ob;
        string msg; 
        int phase = get_current_day_phase(); 
        int extra,count = 0;
 
        
         if( !target ) target = offensive_target(me);
         if( !target || !target->is_character() || !me->is_fighting(target) )
               return notify_fail("「眩刀」只能對戰鬥中的對手使用。\n");
        
         
        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");
        
        if (phase < 0 || phase > 5) {tell_object(me,"沒有日光怎麼用「眩刀」？\n");return 1;}

          if( uptime()-query_temp("last_pf_time", me)<2 )
          return notify_fail("出奇才能至勝。\n");
         //用冰刀加2招
         if( query("id", weapon) == "iceblade")count=2;
         
           
         
        if( query("neili", me)<200 )
                return notify_fail("你的內力不夠了！\n");

        if( (int)me->query_skill("blade") < 160 ||
            me->query_skill_mapped("blade") != "bingpo-blade")
                return notify_fail("你的「基本刀法」還不到家，無法使用「眩刀」！\n");
        
        if( (int)me->query_skill("blade") < 160 )
            return notify_fail("你的「冰魄寒刀」還不到家，無法使用「眩刀」！\n");
        
        msg = HIW "$N猛然將刀身一橫，明晃晃的刀身在日光下反射一片白光,直射$n的面門！\n" NOR;
        message_vision(msg, me, target);
        if( random(query("combat_exp", me))>query("combat_exp", target)/2 )
         {  msg = HIW "$N只覺一道眩光刺得雙眼什麼都看不見了，$n見狀大喜連續三刀，從三個不同的方向砍來！\n" NOR;        
            message_vision(msg, target,me);
             extra = me->query_skill("bingpo-blade",1) / 50;
            if(extra>4) extra = 4 ; target->start_busy(extra + count);
          }else{
               msg = "可是$n看破了$N的企圖，往旁一閃躲了過去。\n" NOR;
               message_vision(msg, me, target);
                set_temp("last_pf_time", uptime(), me);
               me->start_busy(1+random(3));
               return 1;
           }
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        addn("force", -150, me);
        me->start_busy(random(1));
        set_temp("last_pf_time", uptime(), me);
        return 1;
}



int get_current_day_phase() {
    // ref. /adm/daemons/natured.c:init_day_phase()
    mixed *local = localtime(time()*60);
    int t = local[2] * 60 + local[1];
    int i;
    for (i=0; i<sizeof(day_phase); i++)
        if (t>=day_phase[i]["length"])
            t -= (int)day_phase[i]["length"];
        else
            break;
    return (i==0 ? sizeof(day_phase)-1 : i-1);
}