// fanti.c  無影反踢

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;
#define PNAME "「無影反踢」"
int perform(object me, object target)
{
        object weapon, ob;
        string msg, string1;
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
                
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("「無影反踢」開始時不能拿着兵器！\n");

        fskill = "qingming-xuangong";
        bskill = "leg";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(fskill, 1) < 50 )
                return notify_fail("你的"+to_chinese(fskill)+"不夠使用"+PNAME+"。\n");

        if( (int)me->query_skill(sskill, 1) < 50 )
                return notify_fail("你的"+to_chinese(sskill)+"不到家，無法使用"+PNAME+"。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠！\n");

        msg = HIY "$N的左足反踢而起，直撩$n的下陰！不待$n退開站穩，右足連環反踢，將$n踢得一時無法還手！\n" NOR;

        target->start_busy(random(4));

        message_combatd(msg, me, target);

        for (count=0;count<3;count++)
        {
                if (flag == 1) target = offensive_target(me);
                if (!objectp(target)) break;
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);
        }

        addn("neili", -100, me);
        me->start_busy(random(3));

        if(!target->is_fighting(me)) target->fight_ob(me);
        return 1;
}
string name() {return replace_string(replace_string(PNAME,"「",""),"」","");}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"之"+name()+WHT"："NOR"\n");
        write(@HELP

        使用功效：
                連續出手三腳

        出手要求：
                青冥玄功50級
                無影腿50級
                內力300
HELP
        );
        return 1;
}
