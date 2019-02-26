// suo.c 金鈎鎖魂
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;
#define PNAME "金鈎鎖魂"
int perform(object me, object target)
{
        object ob,weapon,myweapon;
        string msg, string1;
        int skill,myskill,attack_time,i;
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
                
        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "hook" )
                return notify_fail(PNAME"開始時必須拿着一把鈎！\n");

        if( !objectp(weapon=query_temp("weapon", target)) )
                return notify_fail("對方手中並沒有兵器！\n");

        fskill = "wudu-shengong";
        bskill = "hook";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(fskill, 1) < 50 )
                return notify_fail("你的"+to_chinese(fskill)+"還不到家，使不出"+PNAME+"。\n");

        if( (int)me->query_skill(sskill, 1) < 50 )
                return notify_fail("你的"+to_chinese(sskill)+"還不到家，使不出"+PNAME+"。\n");

        if( (int)me->query_skill(bskill, 1) < 50 )
                return notify_fail("你的"+to_chinese(bskill)+"還不到家，使不出"+PNAME+"。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠！\n");

        weapon=query_temp("weapon", target);
        myweapon=query_temp("weapon", me);
        message_combatd(HIR"\n$N虛晃一招，手中"+query("name", myweapon)+HIR"忽的一聲，鈎尖已搭在$n的"+query("name", weapon)+HIR"上！\n"NOR,me,target);
        skill = target->query_skill("parry", 1);
        myskill = me->query_skill(bskill, 1);
            if(random(myskill) < random(skill)||query("max_neili",me) <random(query("max_neili",target))) 
        {
                msg = HIY "可是$n"HIY"早有準備，急忙收招跳開！\n" NOR;
                message_combatd(msg, me,target);
                me->start_busy(2);
                addn("neili", -100, me);
                return 1;
        }

        msg=HIR"只見$N順勢一絞，低喝一聲：“撒手！”$n只覺得虎口一陣巨痛，\n手中"+query("name", weapon)+HIR"噹啷一聲掉在地上！\n"NOR;
        msg += "$N哈哈一笑，得理不饒人，招招進逼！\n" NOR;
        message_combatd(msg, me,target);
        weapon->move(environment(me));

        attack_time = 3 + random(3);
        for(i = 0; i < attack_time; i++)
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);
        target->start_busy(random(2));
        addn("neili", -450, me);
        me->start_busy(2);
        return 1;
}

string name() {return replace_string(replace_string(PNAME,"「",""),"」","");}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"之"+name()+WHT"："NOR"\n");
        write(@HELP

        使用功效：
                連續出手五鈎
                擊落對方兵刃

        出手要求：
                五毒神功50級
                基本鈎法50級
                五毒鈎法50級
                內力500
                使用五毒教的鈎
HELP
        );
        return 1;
}
