// Last Modified by winder on Sep. 12 2001
// chan.c 纏字訣

#include <ansi.h>

inherit F_SSERVER;
#define PNAME "「纏」字訣"
int perform(object me, object target)
{
        object weapon;
        string msg;
        int flag;
        string fskill,sskill,bskill,pfname,pskill;

        sskill = explode(__FILE__,"/")[<2];
        pfname = explode(__FILE__,"/")[<1][0..<3];
  if (userp(me) && !wizardp(me) &&
   !query("perform/"+pfname, me) && 
   !query("can_perform/"+sskill+"/"+pfname, me) && 
   !query_temp("murong/xingyi", me) && 
   !SCBORN_D->valid_perform(me,sskill,pfname))
   return notify_fail("你所使用的外功中沒有這種功能。\n");

        if( !objectp(target) ) {flag =1;target = offensive_target(me);}
        
        if( !target || !target->is_character() || target == me ||        
                  !me->is_fighting(target) ||
          !living(target) || query_temp("noliving", target) )
                return notify_fail(PNAME"只能對戰鬥中的對手使用。\n");
                
        if( !objectp(weapon=query_temp("weapon", me)) || 
                query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( target->is_busy() )
                return notify_fail(target->name()+"目前正自顧不暇，放膽攻擊吧。\n");

        fskill = "honghua-shengong";
        bskill = "sword";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(fskill, 1) < 40 )
                return notify_fail("你的"+to_chinese(fskill)+"不夠嫻熟，使不出"+PNAME+"。\n");

        if( (int)me->query_skill(sskill, 1) < 40 )
                return notify_fail("你的"+to_chinese(sskill)+"不夠嫻熟，不會使用"+PNAME+"。\n");

        if( query("max_neili", me)<300 )
                return notify_fail("你的內力修為不夠！\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠！\n");

        msg = HIG"$N使出落花十三劍「纏」字訣，連遞數個虛招企圖擾亂$n的攻勢。\n";

        me->start_busy(1);
        if( random(query("combat_exp", me))>query("combat_exp", target)/3 )
        {
                msg += HIR "結果$p被$P攻了個措手不及！\n" NOR;
                target->start_busy( (int)me->query_skill(bskill,1) / 30 );
        } else {
                msg += "可是$p神定氣閒，看破了$P的企圖。\n" NOR;
        }
        addn("neili", -100, me);
        message_combatd(msg, me, target);

        return 1;
}
string name() {return replace_string(replace_string(PNAME,"「",""),"」","");}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"之"+name()+WHT"："NOR"\n");
        write(@HELP

        使用功效：
                遲滯對手出招

        出手要求：
                紅花神功40級
                落花十三劍40級
                內力修為300
                內力200
HELP
        );
        return 1;
}
