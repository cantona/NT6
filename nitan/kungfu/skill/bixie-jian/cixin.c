// cixin.c  辟邪劍法「刺心」
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>
#define PNAME "「刺心」"
inherit F_SSERVER;
int perform(object me, object target)
{
        int damage;
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
                
        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("你要使出"PNAME"，手上自然要有劍。\n");

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
        if( (int)me->query_skill(sskill, 1) < 180 )
                return notify_fail("你的"+to_chinese(sskill)+"不夠嫻熟，使不出"+PNAME+"。\n");
        if( query("max_neili", me)<1000 )
                return notify_fail(RED"你內力修為不足，無法運足內力。\n"NOR);
        if( query("neili", me)<600 )
                return notify_fail("你現在內力不夠，沒能將"PNAME"使完！\n");

        msg = HIC "突然之間，$N"HIC"一聲大喝，"+weapon->name()+HIC"電閃而前，直刺$n"HIC"心口！\n"NOR;

        if( random(query("combat_exp", me))>query("combat_exp", target)/4 )
        {
                me->start_busy(2);
                addn("neili", -500, me);
                target->start_busy(random(3));
                damage = (int)me->query_skill(bskill, 1);
                damage = damage + random(damage);
                target->receive_damage("qi",damage+random(damage/2),me);
                target->receive_wound("qi", damage,me);
    target->receive_damage("jing",damage/3+random(damage/3),me);
                target->receive_wound("jing", damage/3,me);
                msg += HIC "$n"HIC"大駭之下，忙伸手招架，哪裏還來得及，卟的一聲，劍尖已刺中$n"HIC"心口。\n"NOR;
                message_combatd(msg, me, target);
        } else
        {
                me->start_busy(2);
                addn("neili", -300, me);
                msg += HIY"$n"HIY"情急智生，抬手也往$N"HIY"心口刺去，迫得$P回劍躍開。\n"NOR;
                message_combatd(msg, me, target);
        }
        if(!target->is_fighting(me)) target->fight_ob(me);
        return 1;
}
string name() {return replace_string(replace_string(PNAME,"「",""),"」","");}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"之"+name()+WHT"："NOR"\n");
        write(@HELP

        使用功效：
                施招刺對方的心口
                此招為辟邪劍法招勢之最，陰險毒辣
                損傷對方氣血和精氣

        出手要求：
                辟邪劍法180級
                葵花心法100級
                最大內力1000
                內力600
HELP
        );
        return 1;
}