// Last Modified by winder on Sep. 12 2001
// zhuihun.c 一劍追魂

#include <ansi.h>;
inherit F_SSERVER;
#define PNAME "一劍追魂"
int perform(object me, object target)
{
        object weapon;
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
                
        if( !objectp(weapon=query_temp("weapon", me)) || 
                query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        fskill = "honghua-shengong";
        bskill = "sword";
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(fskill, 1) < 120 )
                return notify_fail("你的"+to_chinese(fskill)+"不夠高，不能使用"+PNAME+"。\n");

        if( (int)me->query_skill(sskill, 1) < 120 )
                return notify_fail("你的"+to_chinese(sskill)+"不夠嫻熟，不會使用"+PNAME+"。\n");

        damage = (int)me->query_skill("force", 1);
        damage += (int)me->query_skill(bskill, 1)*3/2;

        if( query("max_neili", me)<damage+100 )
                return notify_fail("你的內力修為太弱，使不出「一劍追魂」。\n");

        if( query("neili", me)<damage )
                return notify_fail("你現在內力太弱，不能使用「一劍追魂」。\n");
                        
        msg = CYN "$N微微一笑，猛吸一口氣，飛身躍起，"+weapon->name()+CYN"如無常索命索，絞向$n。\n"NOR;

        if (random(me->query_skill("force")) > target->query_skill("force")/5 )
        {
                target->receive_damage("qi", damage,me);
                target->receive_wound("qi", damage/2,me);
                addn("neili", -(damage/4), me);
                msg += HIR "$n只覺劍勢如夜幕般舖天蓋地般壓來，一時間眼前一花，兩耳轟鳴，無從招架！！\n"NOR;
                me->start_busy(1);
        } else 
        {
                msg += CYN"可是$p見機極快，飛身躍出了$P的劍網。\n"NOR;
                addn("neili", -100, me);
                me->start_busy(1+random(1));
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
                傷害對方氣血

        出手要求：
                紅花神功120級
                追魂奪命劍120級
                足夠的內力修為
                足夠的內力
HELP
        );
        return 1;
}
