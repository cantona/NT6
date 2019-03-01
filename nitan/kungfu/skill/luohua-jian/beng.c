// Last Modified by winder on Sep. 12 2001
// beng.c 崩字訣

#include <ansi.h>;
inherit F_SSERVER;
#define PNAME "「崩」字訣"
int perform(object me,object target)
{
        object weapon, weapon2;
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
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(fskill, 1) < 80 )
                return notify_fail("你的"+to_chinese(fskill)+"還不到家，無法使用"+PNAME+"。\n");

        if( (int)me->query_skill(sskill, 1) < 80 )
                return notify_fail("你的"+to_chinese(sskill)+"還不到家，無法使用"+PNAME+"。\n");

        if( query("max_neili", me)<600 )
                return notify_fail("你的內力修為不夠！\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠！\n");

        if( !objectp(weapon2=query_temp("weapon", target)) )
                return notify_fail("對方沒有用兵刃，你用不了「崩」字訣。\n");

        msg = HIY "$N穩住身形，吐氣開聲，劍柄一橫，使出落花劍“崩”字訣！\n"NOR;
        message_combatd(msg, me);
        
        if( random(query("str", me))>query("str", target)/2 && 
                query("combat_exp", me)>query("combat_exp", target)/4*3 )
        {
                msg = HIY"$n"HIY"只覺得虎口劇痛，手中";
                msg += weapon2->name();
                msg += HIY"頓時把捏不住脫手飛了出去！\n" NOR;
                addn("neili", -150, me);
                target->start_busy(2);
                weapon2->move(environment(me));
        }
        else
        {
                addn("neili", -50, me);
                msg = HIY"可是$n"HIY"看出了$N"HIY"的企圖，立刻手上加勁，將" + weapon2->name() + HIY"奮力向外一擋，\n雙方兵刃的碰在一起,“鐺”的發出一聲巨響。\n"NOR;
                me->start_busy(2);
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
                擊落對方兵刃

        出手要求：
                紅花神功80級
                落花十三劍80級
                內力修為600
                內力500
HELP
        );
        return 1;
}
