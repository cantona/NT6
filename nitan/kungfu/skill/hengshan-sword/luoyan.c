// luoyan.c 回風落雁
// Last Modified by ahda on Aug.31 2001

#include <ansi.h>
inherit F_SSERVER;
#define PNAME "「回風落雁」"

int perform(object me,object target)
{
        string msg;
        object weapon;
        int ap,dp,qi_wound;
        int flag;
        string fskill,sskill,bskill,pfname,pskill;

        sskill = explode(__FILE__,"/")[<2];
        pfname = explode(__FILE__,"/")[<1][0..<3];
  if (userp(me) && !wizardp(me) &&
   !query("perform/"+pfname, me) && 
   !query("can_perform/"+sskill+"/"+pfname, me) && 
   !query_temp("murong/xingyi", me) && 
   !SCBORN_D->valid_perform(me,sskill,pfname) )
   return notify_fail("你所使用的外功中沒有這種功能。\n");

        if( !objectp(target) ) {flag =1;target = offensive_target(me);}
        
        if( !target || !target->is_character() || target == me ||        
                  !me->is_fighting(target) ||
          !living(target) || query_temp("noliving", target) )
                return notify_fail(PNAME"只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
                query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        fskill = "huiyan-xinfa";
        bskill = "sword";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(fskill, 1) < 80 )
                return notify_fail("你的"+to_chinese(fskill)+"等級不夠, 不能使用"+PNAME+"。\n");

        if( (int)me->query_skill(sskill, 1) < 80 )
                return notify_fail("你的"+to_chinese(sskill)+"等級不夠, 不能使用"+PNAME+"。\n");

        if( query("neili", me)<250 )
                return notify_fail("你的內力不夠，無法運用"PNAME"！\n");

        msg = HIC"$N"HIC"一聲長嘯，劍附內力，一式「回風落雁」，"+weapon->name()+HIC"疾如閃電，瞬間罩住$n"HIC"全身各處大穴。\n劍影中，只見$N微一側身，右手翻轉，寒光中"+weapon->name()+"突然自上而下刺出，直指$n"HIC"身上要害 \n" NOR;
        message_combatd(msg, me, target);

        ap=query("combat_exp", me);
        dp=query("combat_exp", target)/3;
        if( dp < 1 ) dp = 1;
        if( random(ap) > dp )
        {
                if( userp(me))addn("neili", -200, me);
                msg = HIY"$n頓時覺得眼前金光亂閃，雙耳嗡嗡內鳴，不知那裡一陣刺痛如針紮一般！\n" NOR;
                qi_wound = (int)me->query_skill(bskill,1) * 2;
                qi_wound = qi_wound/2 + random(qi_wound);

                target->receive_damage("qi", qi_wound,me);
                target->receive_wound("qi", qi_wound/2,me);
                target->start_busy(2);
                me->start_busy(random(3));
        }
        else
        {
                if( userp(me))addn("neili", -100, me);
                msg =HIW"可是$n寧神靜氣，隨手將$N的招數撇在一邊。\n"NOR;
                me->start_busy(random(3));
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
                損傷對方氣血

        出手要求：
                回雁心法80級
                衡山劍法90級
                內力250
HELP
        );
        return 1;
}