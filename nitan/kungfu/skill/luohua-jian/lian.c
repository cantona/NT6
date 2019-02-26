// Last Modified by winder on Sep. 12 2001
// lian.c 紅花十三劍法「連」字訣

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;
#define PNAME "「連」字訣"
int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, attack_time,sword_lvl;
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
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(fskill, 1) < 120 )
                return notify_fail("你的"+to_chinese(fskill)+"不夠嫻熟，使不出"+PNAME+"。\n");

        if( (int)me->query_skill(sskill, 1) < 120 )
                return notify_fail("你的"+to_chinese(sskill)+"不夠嫻熟，不會使用"+PNAME+"。\n");

        if( query("max_neili", me)<500 )
                return notify_fail("你的內力修為不夠！\n");

        if( query("neili", me)<400 )
                return notify_fail("你的真氣不夠！\n");

        addn("neili", -200, me);

        msg = HIY"$N"HIY"使出紅花十三劍法「連」字訣，招式陡然變快，瘋狂的撲向$n！\n"NOR;
        message_combatd(msg, me, target);
        if( random(query("combat_exp", me))>query("combat_exp", target)/20 )
        {
                attack_time = random((int)me->query_skill(bskill, 1)/20);
                sword_lvl=(int)me->query_skill(bskill,1)/10;
                if(attack_time < 2) attack_time = 2;
                if(attack_time > 10) attack_time = 10;
                if(attack_time > 5) 
                {
                        attack_time = attack_time - 4;
                        attack_time = 5 + random(attack_time);
                }

                msg = YEL"結果$p被$P一輪急攻，毫無還手餘裕。\n"NOR;
                for(i = 0; i < attack_time; i++)
                {
                        if (flag == 1) target = offensive_target(me);
                        if (!objectp(target)) break;
                        addn_temp("apply/dodge", sword_lvl, me);
                        addn_temp("apply/attack", sword_lvl, me);
                        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);
                }
                addn_temp("apply/dodge", -sword_lvl*i, me);
                addn_temp("apply/attack", -sword_lvl*i, me);
                me->start_busy(2);
                target->start_busy(1);
        }
        else
        {
                msg = CYN"可是$p出手在先，一下就制住了$P的劍路。\n"NOR;
                me->start_busy(1);
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
                對敵人連續出手

        出手要求：
                紅花神功120級
                落花十三劍120級
                內力修為500
                內力400
HELP
        );
        return 1;
}
