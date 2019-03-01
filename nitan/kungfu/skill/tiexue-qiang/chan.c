// chan.c 鐵血槍法「纏繞」訣
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>

inherit F_SSERVER;
#define PNAME "「纏繞」訣"
int perform(object me, object target)
{
        string msg;
        object weapon;
        int flag;
        string fskill,sskill,bskill,pfname,pskill;

        sskill = explode(__FILE__,"/")[<2];
        pfname = explode(__FILE__,"/")[<1][0..<3];
/*
  if (userp(me) && !wizardp(me) &&
   !query("perform/"+pfname, me) && 
   !query("can_perform/"+sskill+"/"+pfname, me) && 
   !query_temp("murong/xingyi", me) && 
   !SCBORN_D->valid_perform(me,sskill,pfname))
   return notify_fail("你所使用的外功中沒有這種功能。\n");
*/

        if( !objectp(target) ) {flag =1;target = offensive_target(me);}
        
        if( !target || !target->is_character() || target == me ||        
                  !me->is_fighting(target) ||
          !living(target) || query_temp("noliving", target) )
                return notify_fail(PNAME"只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
                query("skill_type", weapon) != "club" )
                return notify_fail("你使用的武器不對。\n");
                
        fskill = "guiyuan-tunafa";
        bskill = "club";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(fskill, 1) < 50 )
                return notify_fail("你的"+to_chinese(fskill)+"火候不夠，使不出"+PNAME+"。\n");

        if( (int)me->query_skill(sskill, 1) < 50 )
                return notify_fail("你的"+to_chinese(sskill)+"火候不夠，使不出"+PNAME+"。\n");

        if( query("max_neili", me)<300 )
                return notify_fail("你的內力修為不足，使不出「纏繞」訣。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的內力不足，使不出「纏繞」訣。\n");

        if( target->is_busy() )
                return notify_fail(target->name()+"目前正自顧不暇，放膽攻擊吧！\n");

        msg = CYN "$N"CYN"使出鐵血槍法「纏繞」訣，手中"+weapon->name()+CYN"如靈蛇扭動，在$n"CYN"的下三路挑、撥、撩、纏，\n";

        me->start_busy(random(3));
        addn("neili", -150, me);
        if( random(query("combat_exp", me))>query("combat_exp", target)/2 )
        {
                msg += "結果$p被$P搞的心情大亂，手忙腳亂起來！\n" NOR;
                target->start_busy( (int)me->query_skill(bskill) / 40);
        } else {
                msg += "$p不理$P的虛招，出手沒有絲毫遲滯。\n" NOR;
        }
        message_combatd(msg, me, target);

        if(!target->is_fighting(me)) target->fight_ob(me);
        return 1;
}

int help(object me)
{
        write(WHT"\n鐵血槍法之纏繞訣"NOR"\n");
        write(@HELP

        使用功效：
                遲滯對方出手

        出手要求：
                歸元吐納法50級
                鐵血槍法50級
                內力修為300
                內力200
HELP
        );
        return 1;
}
