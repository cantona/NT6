// ningxue.c 凝血神爪
// Last Modified by sir on 5/5/2001

#include <ansi.h>
inherit F_SSERVER;
#define PNAME "凝血神爪"
int perform(object me, object target)
{
        string msg;
        int damage,skill;
        object weapon;
        string limb;
        mapping limbs;
        int flag;
        string fskill,sskill,bskill,pfname,pskill;

        sskill = explode(__FILE__,"/")[<2];
        pfname = explode(__FILE__,"/")[<1][0..<3];
  if (userp(me) && !wizardp(me) &&
   !query("perform/"+pfname, me) && 
   !query("can_perform/"+sskill+"/"+pfname, me) && 
   !query_temp("murong/xingyi", me) 
    )
   return notify_fail("你所使用的外功中沒有這種功能。\n");

        if( !objectp(target) ) {flag =1;target = offensive_target(me);}
        
        if( !target || !target->is_character() || target == me ||        
                  !me->is_fighting(target) ||
          !living(target) || query_temp("noliving", target) )
                return notify_fail(PNAME"只能對戰鬥中的對手使用。\n");
                
        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("你必須空手運功。\n");

        if((int)me->query_str() < 30)
                return notify_fail("你膂力不夠，不能使用凝血神爪！\n");

        fskill = "yunlong-shengong";
        bskill = "claw";
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(fskill, 1) < 120 )
                return notify_fail("你的"+to_chinese(fskill)+"修為不夠，目前還不能使用"+PNAME+"。\n");

        if( (int)me->query_skill(sskill, 1) < 150 )
                return notify_fail("你的"+to_chinese(sskill)+"修為不夠，目前還不能使用"+PNAME+"。\n");

        if( query("neili", me)<800 )
                return notify_fail("你內力現在不夠，不能使用凝血神爪！\n");

        if( target->is_busy() )
                return notify_fail(target->name()+"目前正自顧不暇，放膽攻擊吧！\n");

        msg = HIR "$N使出雲龍爪絕技「凝血神爪」，真氣灌注雙爪抓向$n。\n"NOR;

        if( random(query("combat_exp", me))>query("combat_exp", target)/4 )
        {
    if( arrayp(limbs=query("limbs", target)) )
         limb = limbs[random(sizeof(limbs))];
    else
         limb = "要害";
                msg+=HIR "$n連忙騰挪躲閃，然而“撲哧”一聲，$N"
         HIR "五指正抓在$n" HIR "的" + limb + "，只聽得$n"
         HIR "一聲慘叫，鮮血橫飛。\n" NOR;
                 skill = me->query_skill(bskill, 1) * 2;
                damage = skill + (int)me->query_skill("force", 1)/2;
                addn("neili", -300, me);
                me->start_busy(2);
                target->start_busy(random(3));
                target->receive_damage("qi", damage,me);                
                target->receive_wound("qi", damage/4,me);
                target->receive_damage("jing", damage*7/10,me);
                target->receive_wound("jing", damage/3,me);
                addn("neili", -600, target);
        }
        else {
                msg += HIG "可是$p看破了$P的企圖，騰身避開,並沒有中招。\n" NOR;
                me->start_busy(4);
                addn("neili", -100, me);
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
                傷敵氣血和精氣

        出手要求：
                雲龍神功120級
                雲龍爪150級
                後天膂力30
                內力800
HELP
        );
        return 1;
}
