// kuai.c 快劍

#include <ansi.h>

inherit F_SSERVER;
#define PNAME "「快劍」"
int perform(object me, object target)
{
        object weapon;
        int dodge, parry, sword, busy_time;
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
                
        if( query_temp("pfm-target/xunlei-kuai", target) )
                return notify_fail("對手已被昆侖「快劍」心法所困。\n");        

        weapon=query_temp("weapon", me);

        if( !objectp(weapon) || query("skill_type", weapon) != "sword" )
                return notify_fail("你手中無劍，怎能運用「快劍」心法？！\n");

        fskill = "xuantian-wuji";
        bskill = "sword";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(fskill, 1) < 120 )
                return notify_fail("你的"+to_chinese(fskill)+"修為火候未到，施展"+PNAME+"只會傷及自身。\n");

        if( (int)me->query_skill(sskill, 1) < 120 )
                return notify_fail("你的"+to_chinese(sskill)+"修為還不夠，還未領悟"+PNAME+"。\n");

        if( me->query_skill_mapped("force") != fskill)
                return notify_fail("你所用內功與「快劍」心法相悖！\n");

        if( query("max_neili", me) <= 1500 )
                return notify_fail("你的內力修為不足，勁力不足以施展「快劍」！\n");

        if( query("neili", me) <= 700 )
                return notify_fail("你的內力不夠，勁力不足以施展「快劍」！\n");

        if( query("qi", me) <= 200 )
                return notify_fail("你的氣血有限，不足以施展「快劍」！\n");
        
        dodge = target->query_skill("dodge", 1)/3;
        parry = target->query_skill("parry", 1)/3;
        sword = me->query_skill(bskill, 1)/3;
        busy_time = me->query_skill(bskill, 1)/30;        
        
        message_combatd(HIW"$N飄身而起，使出昆侖絕技「快劍」心法，頓時劍意空靈飄逸，似萬千柳絮飛舞，\n" NOR, me, target);
        
        if( random(query("combat_exp", me))>query("combat_exp", target)/5 )
        { 
                message_combatd(HIW"又如和風陣陣拂過。$n"HIW"眼花繚亂，被攻了個措手不及！\n" NOR, me, target);
                addn_temp("apply/dodge", -dodge, target);
                addn_temp("apply/parry", -parry, target);
                addn_temp("apply/attack", -sword, target);
                target->start_busy(busy_time);
                set_temp("pfm-target/xunlei-kuai", 1, target);
                addn("neili", -300, me);
                addn("qi", -100, me);
                target->start_call_out( (: call_other, __FILE__, "remove_effect",me,target, dodge, parry,  sword :), sword/3);
        }
        else
        {
                message_combatd(HIW"可$n"HIW"鎮定自若，絲毫不為所動！\n"NOR, me, target);
                me->start_busy(1);
                addn("neili", -200, me);
                addn("qi", -100, me);
        }
        return 1;
}

void remove_effect(object me,object victim, int dodge, int parry, int sword)
{
        if (objectp(victim))
        {
                delete_temp("pfm-target/xunlei-kuai", victim);
                addn_temp("apply/dodge", dodge, victim);
                addn_temp("apply/parry", parry, victim);
                addn_temp("apply/attack", sword, victim);
        }
        
        if (objectp(me) && objectp(victim) && victim->is_fighting(me))
        {
                message_combatd(HIY "\n\n$N"HIY"漸漸適應了$n"HIY"的劍路，攻守自如多了。\n" NOR, victim, me);
        }
}
string name() {return replace_string(replace_string(PNAME,"「",""),"」","");}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"之"+name()+WHT"："NOR"\n");
        write(@HELP

        使用功效：
                損害對方攻防
                遲滯對方出手

        出手要求：
                玄天無極功120級
                迅雷十六劍120級
                內力1500
                氣血200
HELP
        );
        return 1;
}
