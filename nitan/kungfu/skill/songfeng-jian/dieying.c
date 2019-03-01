// dieying.c 鬆間蝶影
// Last Modified by sir on 4/25/2001



#include <ansi.h>

inherit F_SSERVER;
#define PNAME "「鬆間蝶影」"
int perform(object me,object target)
{
        string msg;
        object weapon ;
        int skill, /*ap,*/ dp, neili_wound, qi_wound;
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

        if( (int)me->query_skill(fskill, 1) < 120 )
                return notify_fail("你的"+to_chinese(fskill)+"等級不夠, 不能使用"+PNAME+"。\n");

        if( (int)me->query_skill(sskill, 1) < 150 )
                return notify_fail("你的"+to_chinese(sskill)+"等級不夠, 不能使用"+PNAME+"。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的內力不夠，無法運用「鬆間蝶影」！\n");

        msg = HIG "$N"HIG"凝神息氣，劍附內力，一式「鬆間蝶影」，"+weapon->name()+HIG "挽出千萬朵劍花，劍影如蝶般撲向$n"HIG"。\n";
        message_combatd(msg, me, target);

        skill = me->query_skill(bskill,1);
  dp = target->query_skill("force");
        if( dp < 1 ) dp = 1;
//        if( random(skill) > dp/2 ) //相同100級就是 random(100) > 150/2  好低...
        if ( random(skill) > dp/4 ) // random(100) > 150/4  now
        {
                if( userp(me))addn("neili", -150, me);
                msg ="$n頓時覺得眼前蝶影飄飛，雙耳嗡嗡內鳴，全身上下一陣刺痛如針紮一般！\n" NOR;
                qi_wound = 2 * skill;
                qi_wound = qi_wound/2 + random(qi_wound);

                target->receive_damage("qi", qi_wound,me);
                target->receive_wound("qi", qi_wound/2,me);
                target->start_busy(2);
           me->start_busy(1+random(3));
        }
        else
        {
                addn("neili", -50, me);
                msg = "可是$n寧心靜氣，身行虛晃，躍出劍影。\n"NOR;
                me->start_busy(1+random(3));
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
                傷敵氣血並使其暫時不能動彈。

        出手要求：
                青冥玄功120級
                鬆風劍法150級
                內力300
HELP
        );
        return 1;
}