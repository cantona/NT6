// shuangjue.c  拳腿雙絕

#include <ansi.h>
inherit F_SSERVER;
#define PNAME "「拳腿雙絕」"
int perform(object me, object target)
{
        int i, j, z, y;
        int flag;
        string fskill,sskill,bskill,pfname,pskill,cskill,cskill1;

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

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手使用「拳腿雙絕」！\n");
                
        fskill = "xuantian-wuji";
        bskill = "leg";
        cskill = "cuff";
        cskill1= "zhentian-cuff";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
                cskill = "force";
                cskill1= "shenyuan-gong";
        }
        if( !query_temp("murong/xingyi", me) )
        {
                if (me->query_skill_prepared("cuff") != "zhentian-cuff" ||
                        me->query_skill_prepared("leg") != "chuanyun-leg" ||
                        me->query_skill_mapped("cuff") != "zhentian-cuff" ||
                        me->query_skill_mapped("leg") != "chuanyun-leg")
                        return notify_fail("你現在無法使用"PNAME"進行攻擊！\n");
        }
        if( (int)me->query_skill(cskill1, 1) < 100 )
                return notify_fail("你的"+to_chinese(cskill1)+"不夠嫻熟，無法施展"PNAME"。\n");
        if( (int)me->query_skill(cskill, 1) < 100 )
                return notify_fail("你的"+to_chinese(cskill)+"不夠嫻熟，無法施展出"PNAME"。\n");
        if( (int)me->query_skill(bskill, 1) < 100 )
                return notify_fail("你的"+to_chinese(bskill)+"不夠嫻熟，無法施展出"PNAME"。\n");
        if( (int)me->query_skill(sskill, 1) < 100 )
                return notify_fail("你的"+to_chinese(sskill)+"不夠嫻熟，無法施展"PNAME"。\n");
        if ((int)me->query_skill(fskill, 1) < 100)
                return notify_fail("你的"+to_chinese(fskill)+"火候不夠，無法施展出"PNAME"。\n");
        if( (int)me->query_dex() < 30 )
                return notify_fail("你的身法欠佳，無法施展出"PNAME"。\n");
        if( query("max_neili", me)<500 )
                return notify_fail("你的內力不夠，無法施展出"PNAME"。\n");
        if( query("neili", me)<400 )
                return notify_fail("你的真氣不夠，無法施展出"PNAME"。\n");
        i = me->query_skill(cskill,1);
        j = me->query_skill(bskill,1);
        z = me->query_skill("force",1);
        y = (i+j+z)/20;
        message_combatd(RED"$N"RED"一聲清嘯，拳腳齊施，使出崑崙絕學「拳腿雙絕」迅捷無倫地攻向$n"RED"！\n"NOR,me, target);
        addn("neili", -400, me);
        addn_temp("apply/str", y, me);
        addn_temp("apply/attack", y, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        addn_temp("apply/str", -y, me);
        addn_temp("apply/attack", -y, me);
        me->start_busy(2);
        return 1;
}

string name() {return replace_string(replace_string(PNAME,"「",""),"」","");}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"之"+name()+WHT"："NOR"\n");
        write(@HELP

        使用功效：
                加力連續出手五招

        出手要求：
                玄天無極功100級
                基本腿法100級
                基本拳法100級
                震天拳法100級
                穿雲腿100級
                後天身法30
                內力修為500
                內力400
HELP
        );
        return 1;
}