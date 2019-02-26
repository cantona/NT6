//  tianditongshou 天地同壽
// Last Modified by Winder on Feb. 18 2001

#include <ansi.h>;
inherit F_SSERVER;
#define PNAME "「天地同壽」"
int perform(object me, object target)
{
        object weapon;
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
                return notify_fail("你沒裝備劍就想使「天地同壽」？\n"NOR);

                if( !query("wudang/yinliting_teach", me) )
                        return notify_fail("你未得殷梨亭傳授，不會使用天地同壽。\n");

        fskill = "taiji-shengong";
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
                return notify_fail("你的"+to_chinese(fskill)+"的修為不夠，不能使用"+PNAME+"。\n");

        if( (int)me->query_skill(sskill, 1) < 120 )
                return notify_fail("你的"+to_chinese(sskill)+"不夠嫻熟，不會使用"+PNAME+"。\n");

        if( (int)me->query_dex() < 30 )
                return notify_fail("你的身法太低，不能使用天地同壽。\n");

        if( query("neili", me)>100 || query("qi", me)>200 )
                return notify_fail("天地同壽是拼命的招數，怎可隨便使用？！\n");

        message_combatd(RED"\n$N"RED"猛然不顧一切進身到$n"RED"面前，突然反轉身行，借勢將手中的利劍向自己\n的小腹刺去，意圖和$n"RED"拼個玉石俱焚。\n\n"NOR, me, target);

        if( random(query("combat_exp", me))>query("combat_exp", target)/4
                && me->query_dex() > (int)target->query_dex()/2)
        {
                message_combatd(HIR"\n$n"HIR"被如此兇悍的招數，嚇的全身冰涼，呆立不動，但見$N"HIR"手中的利劍從自\n己的小腹刺入後，直接洞穿了$n"HIR"的身體！\n"NOR, me, target);
                tell_object(target, HIR"你感覺一柄利劍從自己身體穿過，駭怖到了極點！\n" NOR);
                addn("max_neili", -100, me);
                set_temp("last_damage_from", "使用天地同壽和"+target->name()+"同歸於盡", me);
                me->receive_wound("qi",query("max_qi", me)+200,target);
                set_temp("last_damage_from", "被"+me->name()+"使用天地同壽殺", target);
                target->receive_wound("qi",query("max_qi", target)+200,me);
                target->start_busy(3 + random(3));
                me->start_busy(3 + random(3));
                target->die();
                me->die();
        }
        else 
        {
                target->start_busy(3 + random(3));
                message_combatd(HIY"\n$n在千鈞一髮之際，急忙推開$N，向上飛起，勉強避開這招，但已被嚇的目瞪口呆。\n"NOR, me, target);
                addn("max_neili", -50, me);
                set_temp("last_damage_from", "使用天地同壽", me);
                me->receive_wound("qi",query("max_qi", me)+200,target);
                me->die();
        }
        return 1;
}

string name() {return replace_string(replace_string(PNAME,"「",""),"」","");}
int sp() {return 1;}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"之"+name()+WHT"："NOR"\n");
        write(@HELP

        使用功效：
                拼卻一死，求得與對手偕亡
                使用者是死定了，慎用。需搏得一個高手方為上算

        出手要求：
                兩儀劍法120級
                太極神功120級
                後天身法30
                內力500
                需殷梨亭親授
HELP
        );
        return 1;
}
