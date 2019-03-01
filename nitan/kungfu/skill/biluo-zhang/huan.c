#include <ansi.h>
 
inherit F_SSERVER;
#define PNAME "「"HIG"幻化煙雲"NOR "」"

int perform(object me,object target)
{
        string msg;
        object weapon, weapon2;
        int skill, ap,dp, damage;
        int flag;
        string fskill,sskill,bskill,pfname;

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

        //空手兵器均可

        fskill = "huiyan-xinfa";
        bskill = "strike";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }
        if( (int)me->query_skill(fskill, 1) < 100 )
                return notify_fail("你的"+to_chinese(fskill)+"火候不夠，使不出"+PNAME+"。\n");
        if( (int)me->query_skill(sskill, 1) < 100 )
                return notify_fail("你的"+to_chinese(sskill)+"不夠熟練，不會使用"+PNAME+"。\n");
        if( (int)me->query_skill(bskill, 1) < 100 )
                return notify_fail("你的"+to_chinese(sskill)+"修為不夠, 使不出"+PNAME+"。\n");
        if(target->is_busy())
                return notify_fail(target->name() +"目前正自顧不暇，放膽攻擊吧！\n");
        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠，使不出"PNAME"！\n");
        msg = HIC "\n$N" HIC "雙掌陡然連續反轉，一招"PNAME+HIC"，雙掌帶風，已將$n" HIC "籠罩在掌風之中。\n" NOR;
 
   ap = me->query_skill(bskill,1);
   dp = target->query_skill("parry",1);
        if( dp < 1 )                dp = 1;
        if( random(ap) > dp/3 )
        {
                msg += HIR "結果$n" HIR "目不暇接，頓時被$N" HIR "掌"
                      "風所困，頓時陣腳大亂。\n" NOR;
                target->start_busy(ap/30+2);
                me->start_busy(1);
                addn("neili", -200, me);
        }
        else
        {
     msg += HIY "$n" HIY "看清$N" HIY "這幾招的來路，但"
                      "內勁所至，掌風犀利，也只得小心抵擋。\n" NOR;          
                me->start_busy(2);
                addn("neili", -50, me);
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
                回雁心法100級
                碧羅掌100級
                基本掌法100級
                內力100
HELP
        );
        return 1;
}