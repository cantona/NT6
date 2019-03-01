//五毒鞭法  聚毒

#include <ansi.h>

inherit F_SSERVER;
#define PNAME "聚毒"
int perform(object me, object target)
{
        string msg;
        object weapon;
        int lvl ;
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
                query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對。\n");

        fskill = "wudu-shengong";
        bskill = "whip";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(fskill, 1) < 50 )
                return notify_fail("你的"+to_chinese(fskill)+"功力太淺，無法"+PNAME+"。\n");

        if( (int)me->query_skill(sskill, 1) < 60 )
                return notify_fail("你的"+to_chinese(sskill)+"功力太淺，無法"+PNAME+"。\n");

        if( query("neili", me)<250 )
                return notify_fail("你的內力不足，無法聚毒！\n");

        addn("neili", -200, me);

        if( target->is_busy() )
                return notify_fail(target->name() +"已經手忙腳亂了，不需要在用毒了。\n");

        lvl = me->query_skill(bskill, 1);
        msg = BLU"$N"BLU"默運內力，將毒氣運于鞭上，只見一股藍色的霧氣罩住了長鞭。\n";
        if( random(query("combat_exp", me))>query("combat_exp", target)/2 && random(lvl)>20 )
        {
                msg += "$p措不及防，不由身染毒氣。\n" NOR;
                target->receive_damage("qi", lvl,me);
                target->receive_wound("qi",15 + random(10),me);
                target->receive_wound("jing", 10,me);
                target->apply_condition("snake_poison", random(lvl/10) + 1 + target->query_condition("snake_poison"));
                me->start_busy(1);
                target->start_busy(1 + random(2));
        }
        else
        {
                msg += HIY"可是$p看出了$P的毒計，立刻屏住呼吸，沒有中毒。\n"NOR;
                me->start_busy(3);
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
                傷敵氣血，使敵手中毒

        出手要求：
                五毒神功50級
                五毒鞭法60級
                內力250
HELP
        );
        return 1;
}
