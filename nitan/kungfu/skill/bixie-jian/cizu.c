// cizu.c 刺足
// Last Modified by winder on Oct. 28 2000

#include <ansi.h>
#define PNAME "「刺足」"
inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
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
                
        if( !objectp(weapon=query_temp("weapon", me)) || 
                query("skill_type", weapon) != "sword" )
                return notify_fail(HIY "沒劍你拿什麼東西去刺人家？\n" NOR);

        fskill = "kuihua-xinfa";
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
                return notify_fail("你的"+to_chinese(fskill)+"火候不夠，使不出"+PNAME+"。\n");
        if( (int)me->query_skill(sskill, 1) < 100 )
                return notify_fail("你的"+to_chinese(sskill)+"不夠熟練，不會使用"+PNAME+"。\n");
        if( query("max_neili", me)<500 )
                return notify_fail(HIY "你的內力修為還不夠火候。\n" HIY);
        if( query("neili", me)<300 )
                return notify_fail(HIY "你現在真氣不足。\n" HIY);
        if( query_temp("bixie/cizu", target) )
                return notify_fail(HIR"對方已經身中"PNAME"了！\n"NOR);

        msg = HIC "$N"HIC"突然前身一探，"+weapon->name()+HIC"如流星追月，迅捷異常地紮向$n"HIC"腳踝，\n"NOR;
        if (random(me->query_dex()) > target->query_dex()/2)
        {
                msg += HIC"$n"HIC"只覺得腳踝一痛，一趔怯，跌在地下！\n"NOR;
                message_combatd(msg, me, target);
                addn("neili", -250, me);
                set_temp("bixie/cizu", 1, target);
                call_out("cizu_end", (int) 4+random(6), me, target);
        } else
        {
                addn("neili", -100, me);
                me->start_busy(2);
                msg += HIY"$n"HIY"疾忙一抬腿，恰恰避過了$N"HIY"的出手一擊。\n"NOR;
                message_combatd(msg, me, target);
        }
        if(!target->is_fighting(me)) target->fight_ob(me);
        return 1;
}

void cizu_end(object me, object target)
{
        message_combatd(HIR"$N強忍腳上劇痛，終于顫顫巍巍地站了起來。\n"NOR, target);
        delete_temp("bixie/cizu", target);
        return;
}
string name() {return replace_string(replace_string(PNAME,"「",""),"」","");}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"之"+name()+WHT"："NOR"\n");
        write(@HELP

        使用功效：
                施招刺對方的雙足要穴
                暫時性使對方失去躲閃能力
                暫時性使對手不能移動

        出手要求：
                辟邪劍法100級
                葵花心法100級
                最大內力500
                內力300
HELP
        );
        return 1;
}