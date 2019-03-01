// sanqing.c  一劍化三清
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>

#define PNAME "「群魔亂舞」"
inherit F_SSERVER;
 
int perform(object me, object target)
{
  object weapon, ob;
        string msg, string1;
        int count,sword_lvl;
        int  i , j;
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
    return notify_fail(PNAME"必須拿著劍才能出！\n");
  if (!userp(me)) return notify_fail("npc不在這裡使用這招。\n");
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
                return notify_fail("你的"+to_chinese(sskill)+"還不到家，無法使用"+PNAME+"。\n");
  if( query("neili", me)<100 )
    return notify_fail("你的真氣不夠！\n");
  msg =  HIM "$N" HIM "默運葵花心法，身形變得奇快無比，接連向$n"
              HIM "攻出數招！\n" NOR;
  message_combatd(msg, me,target);

        sword_lvl = me->query_skill(sskill,1)/15; 
        count = (me->query_skill(sskill,1)-1)/100; 

  for(i=0;i<count+2;i++)
  {
    if (flag == 1) target = offensive_target(me);
    if (!objectp(target)) break;
     addn_temp("apply/attack", sword_lvl, me);
    addn_temp("bixie_hit", 1, me);
    if( i)set_temp("action_flag", 1, me);
    COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
                addn_temp("bixie_hit", -1, me);
    set_temp("action_flag", 0, me);
  }
  addn_temp("apply/attack", -i*sword_lvl, me);
  
  addn("neili", -50, me);
  me->start_busy(1);

  if(flag!=1 && !target->is_fighting(me)) target->fight_ob(me);
  return 1;
}
string name() {return replace_string(replace_string(PNAME,"「",""),"」","");}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"之"+name()+WHT"："NOR"\n");
  write(@HELP

        使用功效：
                連續出手

        出手要求：
                葵花心法100級
                辟邪劍法101級
                內力100
HELP
  );
  return 1;
}