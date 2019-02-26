// yunwu.c 衡山劍法 百變千幻衡山雲霧十三式
// Last Modified by ahda on Sep.1 2001

#include <ansi.h>
#define PNAME "衡山雲霧十三式"
inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int qi_wound;
        int flag;
        string fskill,sskill,bskill,pfname,pskill;

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
                return  notify_fail("你要對誰使用這一絕技？\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("這裏不能攻擊別人! \n");

  notify_fail("你不能攻擊這個人。\n");
        if (!userp(target) && !target->accept_hit(me)) return 0;

        if( !objectp(weapon=query_temp("weapon", me)) || 
                query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");                

        if( target->is_busy() || query("id", target) == "gongpingzi" )
                return notify_fail(target->name()+ "目前正自顧不暇，放膽攻擊吧！\n");

        if( userp(me) && (query("family/master_id", me) != "moda") )
                return notify_fail("你不是莫大的弟子，不能使用絕招！\n");

        fskill = "huiyan-xinfa";
        bskill = "sword";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(fskill, 1) < 180 )
                return notify_fail("你的"+to_chinese(fskill)+"的功力不夠不能使用"+PNAME+"。\n");

        if( (int)me->query_skill(sskill, 1) < 200 )
                return notify_fail("你的"+to_chinese(sskill)+"修為不夠，目前還不能使用"+PNAME+"。\n");

        if( (int)me->query_skill(bskill, 1) < 200 )
                return notify_fail("你的"+to_chinese(bskill)+"根基不夠紮實，目前還不能使用"+PNAME+"。\n");

        if((int)me->query_str() < 40)
                return notify_fail("你膂力不夠,不能使用這一絕技！\n");

        if( query("neili", me)<500 )
                return notify_fail("你內力現在不夠，不能使用"PNAME"！\n");

        if( query("max_neili", me)<2500 )
                return notify_fail("你的內功修為不夠，無法使用衡山雲霧十三式！\n");


        msg = HIC"$N手中"+weapon->name()+"寒光陡閃，猛地反刺，直指$n"HIC"胸口。
這一下出招快極，抑且如夢如幻，正是“百變千幻衡山雲霧十三式”中的絕招！\n";

        if( random(query("combat_exp", me)/3)>query("combat_exp", target)/4 )
        {                                             
                msg += HIY "$p大駭之下，急向後退，嗤的一聲，胸口已給利劍割了一道長長的口子，\n衣衫盡裂，胸口肌肉也給割傷了，受傷雖然不重，卻已驚怒交集，鋭氣大失。\n"+ HIR "$P一劍既佔先機，後着綿綿而至，一柄薄劍猶如靈蛇，顫動不絕，猶如鬼魅，\n一點點鮮血從長劍間濺了出來。\n" NOR;
                qi_wound=query("max_qi", target);
                target->receive_damage("qi", qi_wound/2,me);
                target->receive_wound("qi", qi_wound/2,me);
                target->start_busy(2);
                me->start_busy(3);
                addn("neili", -500, me);
        }
        else
        {
                msg += HIM "可是$p看破了$P的企圖，身子往後側閃，堪堪地躲開了$P這一擊。\n" NOR;
                me->start_busy(3);
                addn("neili", -200, me);
        }
        message_combatd(msg, me, target);
        if(!target->is_killing(me)) target->kill_ob(me);
        return 1;
}
string name() {return replace_string(replace_string(PNAME,"「",""),"」","");}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"之"+name()+WHT"："NOR"\n");
        write(@HELP
        
        使用功效：
                嚴重損傷對方氣血
        
        出手要求：
                回雁心法180級
                衡山劍法200級
                基本劍法200級
                內力2500
                後天膂力40
HELP
        );
        return 1;
}