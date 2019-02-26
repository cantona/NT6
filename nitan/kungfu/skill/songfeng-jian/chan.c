// chan.c 松風劍法「纏」字訣
// Last Modified by winder on Aug. 13 2000

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
                return notify_fail(target->name()+"目前正自顧不暇，放膽攻擊吧！\n");

        fskill = "qingming-xuangong";
        bskill = "sword";
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

        if( (int)me->query_skill(sskill, 1) < 40 )
                return notify_fail("你的"+to_chinese(sskill)+"不嫻熟，使不出"+PNAME+"。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的內力不夠，不會使用「纏」字訣。\n");

        msg = HIG"$N"HIG"使出松風劍法「纏」字訣，將手中劍搭在$n"HIG"兵刃上，劍隨意轉，連綿不絕，使$n"HIG"一時無法變招。\n";
        
        if( random(query("combat_exp", me))>query("combat_exp", target)/4 )
        {
                msg += HIR "結果$p被$P鬧個手忙腳亂，驚慌失措，呆在當場，不知如何應對！\n" NOR;
                target->start_busy((int)me->query_skill("sword", 1)/30);
                addn("neili", -150, me);//-200
        } else {
                msg +=HIY"可是$p看破了$P的企圖，鎮定逾恆，一振振開了$P的劍，全神應對自如。\n" NOR;
                me->start_busy(1);
                addn("neili", -50, me);//-100
        }
        message_combatd(msg, me, target);

        if(!target->is_fighting(me)) target->fight_ob(me);
        return 1;
}
string name() {return replace_string(replace_string(PNAME,"「",""),"」","");}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"之"+name()+WHT"："NOR"\n");
        write(@HELP

        使用功效：
                遲滯對方出手

        出手要求：
                青冥玄功50級
                松風劍法40級
                內力300
HELP
        );
        return 1;
}
