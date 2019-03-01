// Last Modified by winder on May. 15 2001
// hama.c 蛤蟆功絕招

#include <ansi.h>
#define PNAME "「蛤蟆功」"
inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
        int damage, p;
        string msg, dodge_skill;
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
                return notify_fail(PNAME"只能對戰鬥中的對手使用。\n");
                
        if( query_temp("weapon", me) )
                return notify_fail("你必須空手才能使用「蛤蟆功」！\n");

        fskill = "hamagong";
        bskill = "strike";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }
        if( (int)me->query_skill(fskill, 1) < 150 )
                return notify_fail("你的"+to_chinese(fskill)+"不夠熟練，不能使用"+PNAME+"。\n");
        if( (int)me->query_skill(sskill, 1) < 150 )
                return notify_fail("你的"+to_chinese(sskill)+"不夠熟練，不能使用"+PNAME+"。\n");
        if( (int)me->query_skill(sskill, 1) < 100 )
                return notify_fail("你的"+to_chinese(sskill)+"不夠嫻熟，使不出"+PNAME+"。\n");
        if( query("max_neili", me)<2000 )
                return notify_fail("你現在內力修為不足，使不出蛤蟆功絕招！\n");
        if( query("neili", me)<1200 )
                return notify_fail("你現在內力不足，使不出蛤蟆功的絕招！\n");
        if( query_temp("hmg_hama", me) )
                return notify_fail("你剛使完「蛤蟆功」絕招，目前氣血翻湧，無法再次運用！\n");

        msg = BLU"\n$N"BLU"身子蹲下，左掌平推而出，使的正是$N"BLU"生平最得意的「蛤蟆功」絕招，掌風直逼$n"BLU"而去！\n"NOR;        
        set_temp("hmg_hama", 1, me);
        if (random(me->query_skill("force")) > target->query_skill("force") /4 )
        {
                me->start_busy(1);
                target->start_busy(1); 
                addn("neili", -1000, me);
                addn("jing", -10, me);
                damage = (int)me->query_skill(bskill, 1);
                damage = damage*2 + random(damage);
                if( query("neili", me)>query("neili", target)*2)damage+=random(damage);
                target->receive_damage("qi", damage,me);
                target->receive_wound("qi", damage/2,me);
                p=query("qi", target)*100/query("max_qi", target);
                msg += damage_msg(damage, "內傷");
                msg += "( $n"+eff_status_msg(p)+" )\n";
                call_out("perform2", 0, me, target, p);
        } 
        else
        {
                me->start_busy(2);
                target->start_busy(1);
                addn("neili", -300, me);
                tell_object(target, HIY"你但覺一股微風撲面而來，風勢雖然不勁，然已逼得自己呼吸不暢，知道不妙，連忙躍開數尺。\n" NOR);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
                call_out("remove_effect", me->query_con()/6, me);
        }
        message_combatd(msg, me, target); 
        return 1;
}

int perform2(object me, object target, int p)
{
        int damage;
        string msg, dodge_skill;
        string bskill;

        bskill = "strike";
        if (!me->query_skill("strike"),1) bskill = "parry";
        if (!objectp(target) || target->is_ghost() || 
                environment(target)!=environment(me) || 
                !living(me) || query_temp("noliving", me) || me->is_ghost() )
        {
                call_out("remove_effect", me->query_con()/6, me);
                return 1;
        }
        if( !living(target) || query_temp("noliving", target) )
        {
          call_out("remove_effect", me->query_con()/6, me);
                return notify_fail("對手已經不能再戰鬥了。\n");
        }
        if( query("neili", me)<500 )
        {
                call_out("remove_effect", me->query_con()/6, me);
                return notify_fail("你待要再發一掌，卻發現自己內力不夠了！\n");
        }
        msg = BLU"\n$N左掌勁力未消，右掌也跟著推出，功力相疊，「蛤蟆功」掌風排山倒海般湧向$n！\n"NOR;        
        if(random(me->query_skill("force")) > target->query_skill("force")/4 &&
                me->query_skill(bskill, 1) > 150 )
        {
                me->start_busy(1);
                target->start_busy(1);
                addn("neili", -200, me);
                addn("jing", -20, me);
                damage = (int)me->query_skill(bskill, 1);                
                damage = damage*3 + random(damage)*2;
                if( query("neili", me)>query("neili", target)*2 )
                        damage += random(damage);
                target->receive_damage("qi", damage,me);
                target->receive_wound("qi", damage/2,me);
                p=query("qi", target)*100/query("eff_qi", target);
                msg += damage_msg(damage, "內傷");
                msg += "( $n"+eff_status_msg(p)+" )\n";                
                call_out("perform3", 0, me, target, p);
        } 
        else 
        {
                me->start_busy(2);
                addn("neili", -200, me);
                tell_object(target, HIY"你喘息未定，又覺一股勁風撲面而來，連忙躍開數尺，狼狽地避開。\n" NOR);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
                call_out("remove_effect", me->query_con()/4, me);
        }
        message_combatd(msg, me, target); 
        return 1;
}

int perform3(object me, object target, int p)
{
        int damage;
        string msg, dodge_skill;
        string bskill;

        bskill = "strike";
        if (!me->query_skill("strike"),1) bskill = "parry";
        if (!objectp(target) || target->is_ghost() || 
                environment(target)!=environment(me) || 
                !living(me) || query_temp("noliving", me) || me->is_ghost() )
        {
                call_out("remove_effect", me->query_con()/4, me);
                return 1;
        }
        if( !living(target) || query_temp("noliving", target) )
        {
        call_out("remove_effect", me->query_con()/4, me);
        return notify_fail("對手已經不能再戰鬥了。\n");
        }
        if( query("neili", me)<700 )
        {                
                call_out("remove_effect", me->query_con()/4, me);
                return notify_fail("你待要再發一掌，卻發現自己內力不夠了！\n");
        }
        msg = BLU"\n$N雙腿一登，雙掌相並向前猛力推出，$n連同身前方圓三丈全在「蛤蟆功」勁力籠罩之下！\n"NOR;        
        if(random(me->query_skill("force")) > target->query_skill("force")/4 &&
                me->query_skill(bskill, 1) > 199 )
        {
                me->start_busy(2);
                target->start_busy(random(3));
                addn("neili", -300, me);
                addn("jing", -30, me);
                damage = (int)me->query_skill(bskill, 1);                
                damage = damage*5 + random(damage)*2;
                if( query("neili", me)>query("neili", target)*2 )
                        damage += random(damage);
                target->receive_damage("qi", damage,me);
                target->receive_wound("qi", damage/2,me);
                p=query("qi", target)*100/query("eff_qi", target);
                msg += damage_msg(damage, "瘀傷");
                msg += "( $n"+eff_status_msg(p)+" )\n";
        }
        else 
        {
                me->start_busy(4);
                target->start_busy(1);
                addn("neili", -300, me);
                addn("jing", -100, target);
                tell_object(target, HIY"你用盡全身力量向右一縱一滾，搖搖欲倒地站了起來，但總算躲開了這致命的一擊！\n" NOR);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }
        call_out("remove_effect", me->query_con()/2, me);
        message_combatd(msg, me, target); 
        return 1;
}

void remove_effect(object me)
{
        if (!me) return;
        delete_temp("hmg_hama", me);
        tell_object(me, HIC"\n你經過一段時間調氣養息，又可以使用「蛤蟆功」絕招了。\n"NOR); 
}

string name() {return replace_string(replace_string(PNAME,"「",""),"」","");}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"之"+name()+WHT"："NOR"\n");
        write(@HELP

        使用功效：
                剛猛無儔的連續三掌

        出手要求：
                蛤蟆功150級
                基本掌法100級
                內力修為2000
                內力1200
HELP
        );
        return 1;
}
