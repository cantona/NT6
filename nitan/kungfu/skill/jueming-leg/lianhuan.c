//lianhuan.c 連環 perform
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>

inherit F_SSERVER;
#define PNAME "絕命連環腿"
int perform(object me, object target)
{
        int damage;
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
                
        if( target->is_busy() )
                return notify_fail(target->name() + "目前正暈頭轉向，乘機進攻吧□\n");

                //兵器空手均可使用

        fskill = "dulong-dafa";
        bskill = "leg";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(fskill, 1) < 60 )
                return notify_fail("你的"+to_chinese(fskill)+"修為不夠，不能運"+PNAME+"。\n");

        if( (int)me->query_skill(bskill, 1) < 40 )
                return notify_fail(PNAME"需要精湛的"+to_chinese(bskill)+"配合，方能有效施展。\n");

        if( (int)me->query_skill(sskill, 1) < 40 )
                return notify_fail("你的"+to_chinese(sskill)+"修為不足，還不會使用"+PNAME+"。\n");

        if( !query_temp("murong/xingyi", me) )
        {
                if( me->query_skill_mapped("strike") != "huagu-mianzhang" )
                        return notify_fail("你所用的並非化骨綿掌，不能與絕命連環腿配合施展！\n");
                if( me->query_skill_prepared("strike") != "huagu-mianzhang" )
                        return notify_fail("你所備的並非化骨綿掌，不能與絕命連環腿配合施展！\n");
        }
        if( query("neili", me) <= 300 )
                return notify_fail("你的內力不夠使用連環決！\n");

        msg = HIY "\n 突然間$N"HIY"身形騰空而起，凌空向$n"HIY"奮力連踢幾腿！\n" NOR;
        if( random(query("combat_exp", me))>query("combat_exp", target)/2 )
        {

                target->start_busy((int)me->query_skill(bskill, 1) / 20);
                damage = (int)me->query_skill(bskill, 1);
                damage = damage/2 + random(damage);
                target->receive_damage("qi", damage,me);
                target->receive_wound("qi", damage/3,me);
                addn("neili", -damage/10, me);
                if( damage < 40 )
                        msg += HIY"結果$n"HIY"被$N"HIY"的連環腿踢得暈頭轉向！□\n" NOR;
                else msg += HIR"結果$n"HIY"被$N"HIY"的連環腿踢中要害，「哇！」的一口鮮血噴湧而出！\n"NOR;
        }
        else
        {
                msg += "可是$p看破了$P的企圖，巧妙得躲了開去。\n" NOR;
                me->start_busy(1 + random(3));
        }
        message_combatd(msg, me, target);

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
                毒龍大法60級
                基本腿法40級
                絕命腿40級
                內力300
                互備化骨綿掌
HELP
        );
        return 1;
}
