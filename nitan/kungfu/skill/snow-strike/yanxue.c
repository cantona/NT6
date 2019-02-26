// Last Modified by winder on Jul. 9 2001
// yanxue.c  「煙雪春梅」
#include <ansi.h>

inherit F_SSERVER;
#define PNAME "「"HIW"煙雪春梅"NOR"」"
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
                
                //兵器空手均可
                
        fskill = "bingxue-xinfa";
        bskill = "strike";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(fskill, 1) < 50 )
                return notify_fail("你的"+to_chinese(fskill)+"火候不夠，使不出"+PNAME+"。\n");

        if( (int)me->query_skill(sskill, 1) < 50 )
                return notify_fail("你的"+to_chinese(sskill)+"不夠熟練，不會使用"+PNAME+"。\n");

        if( query("max_neili", me)<500 )
                return notify_fail("你的內力修為還不夠高。\n");

        if( query("neili", me)<400 )
                return notify_fail("你的內力不夠。\n");

        msg = HIW"$N"HIW"冰雪心法運轉一週天，全身只覺一股寒氣蒸騰欲出，清嘯一聲，\n飛身而上,施展出「"+HIW"煙雪春梅」，雙手一搓一放,一股凝人氣血的\n狂飆向$n"HIW"鋪天蓋地席捲而去。\n"NOR;
        if(random(me->query_skill(bskill, 1)) > target->query_skill("parry",1)/3)
        { 
                me->start_busy(1+random(1));
                target->start_busy(random(3));
                damage = (int)me->query_skill(bskill, 1)+(int)me->query_skill("force",1)*2;
                damage = damage/2 + random(damage);
                target->receive_damage("qi", damage,me);
                target->receive_wound("qi", damage/2,me);
                addn("neili", -300, me);
                msg +=HIC"$n只見漫天青氣席捲而來，躲無可躲，卒一接觸，便被震得七竅流血，如斷線風箏向後飄去。\n"NOR;
        } else
        {
                me->start_busy(2+random(1));
                msg += HIC"可是$p看破了$P的企圖，輕輕地閃在了一邊。\n"NOR;
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
                傷敵氣血

        出手要求：
                冰雪心法50級
                飛雪映梅掌50級
                內力修為500
                內力400
HELP
        );
        return 1;
}
