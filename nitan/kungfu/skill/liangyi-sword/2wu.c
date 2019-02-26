// 2wu.c 無聲無色
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>
inherit F_SSERVER;
#define PNAME "「無聲無色」"
int perform(object me,object target)
{
        string msg;
        object weapon1, weapon2;
        int skill, ap, dp, neili_wound, qi_wound;
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
                
        if( !objectp(weapon1=query_temp("weapon", me)) || 
                query("skill_type", weapon1) != "sword" )
                return notify_fail("你使用的武器不對。\n");
/*if( !objectp(weapon2=query_temp("secondary_weapon", me) )
                 || query("skill_type", weapon2) != "sword" )
                return notify_fail("你左手使用的武器不對。\n");
*/
        fskill = "xuantian-wuji";
        bskill = "sword";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(fskill, 1) < 100 )
                return notify_fail("你的"+to_chinese(fskill)+"修為不夠，不能使用"+PNAME+"。\n");

        if( (int)me->query_skill(sskill, 1) < 120 )
                return notify_fail("你的"+to_chinese(sskill)+"修為不夠，不能使用"+PNAME+"。\n");

        if( (int)me->query_skill(bskill, 1) < 100 )
                return notify_fail("你的"+to_chinese(bskill)+"修為不夠，使不出"+PNAME+"。\n");

        if( me->query_skill("dodge", 1) < 80)
                return notify_fail("你基本輕功修為不夠，使不出"PNAME"！\n");

        if( query("neili", me)<250 )
                return notify_fail("你的內力不夠，無法運用"PNAME"！\n");

        if( query("max_neili", me)<500 )
                return notify_fail("你的內力修為不夠，無法運用"PNAME"！\n");
        
        skill = me->query_skill(bskill,1);

        msg = HIB "$N輕吸一口氣，突然使出一招“無聲無色”，手中"+weapon1->name()+HIB"灌注兩道相同內勁， 但勁力恰恰相反，劍上所生的蕩激之力、破空之聲，一齊相互抵消，無聲無息疾向$n背後刺去。\n";
        message_combatd(msg, me, target);

        ap = skill * 3;
        dp = target->query_skill("force", 1) * 2;
        if( dp < 1 ) dp = 1;
        if( random(ap) > random(dp) )
        {
                if( userp(me))addn("neili", -250, me);//400
                msg = HIR "$n突見劍刃劃空之聲，已無從閃避！\n" NOR;
                qi_wound = skill * 2;
                qi_wound = qi_wound + random(qi_wound);
//        target->receive_damage("qi", qi_wound/3);
                target->receive_damage("qi", qi_wound*3/4);
                target->receive_wound("qi", qi_wound/3);
                target->start_busy(2);
                me->start_busy(1+random(2));
        }
        else
        {
                addn("neili", -100, me);
                msg = HIY"$n"HIY"猛地一縱而起，只聽一聲輕響，好險！襟袖均堪堪被$N"HIY"的劍尖劃破了。\n"NOR;
                me->start_busy(2+random(1));
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
                玄天無極功100級
                兩儀劍法120級
                基本劍法100級
                基本輕功80級
                內力修為500
                內力250
                
HELP
        );
        return 1;
}
