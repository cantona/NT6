// ruying.c 如影隨形
// Last Modified by winder on May. 29 2001

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
#define PNAME "「如影隨形」"
int perform(object me, object target)
{
        string msg;
        int count;
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
        if( objectp(query_temp("weapon", me)) )
                return notify_fail("使用「如影隨形」時雙手必須空着！\n");
        fskill = "zhanzhuang-gong";
        bskill = "leg";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(fskill, 1) < 100 )
                return notify_fail("你的"+to_chinese(fskill)+"等級不夠，不能使用"+PNAME+"。\n");

        if( (int)me->query_skill(sskill, 1) < 100 )
                return notify_fail("你的"+to_chinese(sskill)+"不夠嫻熟，不會使用"+PNAME+"。\n");

        if( (int)me->query_dex() < 27 )
                return notify_fail("你的身法不夠強，不能使用"PNAME"。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你現在內力太弱，不能使用"PNAME"。\n");

        msg = HIY"$N"HIY"忽然身隨掌起，雙腿連環，霎時之間連踢五腿，一腿既出，第二腿如影隨形，緊跟而至。\n" NOR;
        message_combatd(msg, me, target);
        for (count=0;count<5;count++)
        {
                if (flag ==1 ) target = offensive_target(me);
                if (!objectp(target)) break;
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
        }
        addn("neili", -400, me);
        me->start_busy(2+random(2));
        return 1;
}

string name() {return replace_string(replace_string(PNAME,"「",""),"」","");}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"之"+name()+WHT"："NOR"\n");
        write(@HELP

        使用功效：
                可以連續踢出五腿，使敵人無喘息之機，威力強大。
        出手要求：
                站樁功50級
                如影隨形腿100級
                後天身法27
                內力1000
HELP
        );
        return 1;
}
