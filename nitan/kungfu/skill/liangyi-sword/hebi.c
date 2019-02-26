// 崑崙正兩儀劍之雙劍合壁
// Last Modified by Winder on Jun. 23 2001

#include <ansi.h>
inherit F_SSERVER;
#define PNAME "「雙劍合璧」"
int remove_effect(object me);
int remove_effect1(object target);
// 有bug待解決
int perform(object me, string arg)
{
        object weapon, weapon1, target;
        int skill, skill1;
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

        if(!arg) return notify_fail("你想和誰一起合璧？\n");
        if(!objectp(target = present(arg, environment(me))))
                return notify_fail("這裏沒有這個人。\n");
/*需要判斷是否攻擊同一個人*/
        if( !target->is_fighting() ||
                !target->is_character() ||
                !me->is_fighting())
                return notify_fail("合璧只能在戰鬥中使用。\n");
        if( !living(target) || query_temp("noliving", target) )
                return notify_fail(target->name()+"已經無法戰鬥了。\n"); 
        if(target==me) return notify_fail("和自己合璧？\n"); 
        if(me->is_fighting(target))
                return notify_fail("你正在和"+target->name()+"打架呢。\n");
        weapon=query_temp("weapon", me);
        weapon1=query_temp("weapon", target);
        if( !weapon || query("skill_type", weapon) != "sword" || 
                me->query_skill_mapped("sword") != "liangyi-sword" ||
                me->query_skill_mapped("parry") != "liangyi-sword")
                return notify_fail("你現在無法使用「雙劍合璧」。\n");

        if( !weapon1 || query("skill_type", weapon1) != "sword" || 
                target->query_skill_mapped("sword") != "liangyi-sword" ||
                target->query_skill_mapped("parry") != "liangyi-sword")
                return notify_fail(target->name()+"現在無法使用「雙劍合璧」。\n");
        skill = me->query_skill("liangyi-sword", 1);
        skill1 = target->query_skill("liangyi-sword", 1);
        if(skill < 100 )
                return notify_fail("你的兩儀劍法等級不夠，不能使用「雙劍合璧」。\n");
        if((int)me->query_skill("xuantian-wuji", 1) < 100 )
                return notify_fail("你的玄天無級功等級不夠，不能使用「雙劍合璧」。\n");           
        if( query("neili", me)<500 )
                return notify_fail("你現在真氣太弱，不能使用「雙劍合璧」。\n");
        if( query("max_neili", me)<1000 )
                return notify_fail("你現在內力太弱，不能使用「雙劍合璧」。\n");
        if( query_temp("ly_hebi", me) )
                return notify_fail("你已經在使用「雙劍合璧」了。\n");
        if( query_temp("ly_hebi", target) )
                return notify_fail(target->name()+"已經在和他人使用「雙劍合璧」了。\n");
        if( query_temp("lyhebi_target", me) )
        {
                if( query_temp("lyhebi_target", me) == target )
                        return notify_fail("你已經做好和"+target->name()+"雙劍合璧的準備了。\n");
                else
                {
                        tell_object(query_temp("hebi_target", me),YEL+me->name()+"不打算和你進行雙劍合璧了。\n"NOR);
                        delete_temp("lyprepare_hebi", me);
                        delete_temp("lyhebi_target", me);
                }
        }
        if( query_temp("lyprepare_hebi", target) && 
                query_temp("lyhebi_target", target) == me )
        {
                message_combatd(MAG"\n $N對$n使個眼色,手中"+weapon->name()+MAG+"和$n的"+weapon1->name()+MAG+"交錯相擊，雙劍齊上，頓時只見劍光凌厲，威力大增！\n"NOR, me, target);
                delete_temp("lyprepare_hebi", me);
                delete_temp("lyhebi_target", me);
                delete_temp("lyprepare_hebi", target);
                delete_temp("lyhebi_target", target);
//                me->set_temp("ly_hebi", 1); 
                set_temp("ly_hebi", 1, target);
                addn("neili", -200, me);
                addn("neili", -200, target);
                addn("qi", -50, me);
                addn("qi", -50, target);
                remove_call_out("check_reply");
                me->start_call_out( (: call_other, __FILE__, "check_fight", me, target :), 1);
                target->start_call_out( (: call_other, __FILE__, "check_fight", target, me :), 1);
                me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), (skill+skill1)/2);
                target->start_call_out( (: call_other, __FILE__, "remove_effect", target :), (skill+skill1)/2);
                return 1;
        }
        message_combatd(HIC"\n $N將手中"+weapon->name()+HIC"一橫，暗示$n和$P一起運用雙劍合璧。\n"NOR, me, target);
        tell_object(target, YEL"你如果願意和"+me->name()+"進行雙劍和壁，請也對"+me->name()+"下一次 ( perform hebi <player's id> ) 的命令。\n"NOR); 
        set_temp("lyprepare_hebi", 1, me);
        set_temp("lyhebi_target", target, me);
        set_temp("no_unwield", 1, me);
        set_temp("no_unwield", 1, target);
        call_out("check_reply", 15, me,target); 
        return 1;
}

void check_fight(object me, object target)
{
        object weapon,weapon1;  
        int attack1,attack2,damage1,damage2;

        weapon=query_temp("weapon", me);
        weapon1=query_temp("weapon", target);
//
        if( !query_temp("ly_hebi", me) )
        {
                damage1=(int)me->query_str()*(int)me->query_str()/10;
                damage2=(int)target->query_str()*(int)target->query_str()/10;
                attack1=(int)(me->query_skill("liangyi-sword",1)/5);
                attack2=(int)(target->query_skill("liangyi-sword",1)/5);
                set_temp("ly_hebi", 1, me);
                addn_temp("apply/attack", attack1, me);
                addn_temp("apply/damage", damage1, me);
                set_temp("ly_hebi", 1, target);
                addn_temp("apply/attack", attack2, target);
                addn_temp("apply/damage", damage2, target);
                remove_call_out("remove_effect");
                call_out("remove_effect", 10, me);
                remove_call_out("remove_effect1");
                call_out("remove_effect", 10, target);
        }
//
        if( !weapon || query("skill_type", weapon) != "sword" || 
                me->query_skill_mapped("sword") != "liangyi-sword" ||
                me->query_skill_mapped("parry") != "liangyi-sword")
                call_out("remove_effect", 0, me);
        if( !weapon1 || query("skill_type", weapon1) != "sword" || 
                target->query_skill_mapped("sword") != "liangyi-sword" ||
                target->query_skill_mapped("parry") != "liangyi-sword")
                call_out("remove_effect", 0, me);
        else
                if( (!present(query("id", target),environment(me))) || 
                        !me->is_fighting() ||
                        !living(target) || query_temp("noliving", target) || 
                        !target->is_fighting() ||
                        target->is_ghost() ||
                        me->is_ghost() ||
                        !living(me) || query_temp("noliving", me) || 
                        !query_temp("ly_hebi", target) )
                        call_out("remove_effect", 0, me);
        else call_out("check_fight", 1, me, target);
}
int check_reply(object me,object target )
{
        if( query_temp("lyprepare_hebi", me) )
        {
                delete_temp("lyprepare_hebi", me);

                delete_temp("lyhebi_target", me);
                delete_temp("no_unwield", me);
                delete_temp("no_unwield", target);
                message_combatd(HIY"似乎對方對$N的暗示沒有反應，$N在只好取消了雙劍合壁的請求。\n"NOR, me);
                return 1;
        }
}
int remove_effect(object me)
{
        int attack1, damage1;
        if( query_temp("ly_hebi", me) )
        {
                damage1=(int)me->query_str()*(int)me->query_str()/10;
                attack1=(int)(me->query_skill("liangyi-sword",1)/5);
                delete_temp("ly_hebi", me);
                delete_temp("no_unwield", me);
                addn_temp("apply/attack", -attack1, me);
                addn_temp("apply/damage", -damage1, me);
                message_combatd(HIC"雙劍合璧完結，$N的攻守恢復正常了。\n"NOR, me);
                return 1; 
        }
}
int remove_effect1(object target)
{
        int attack2, damage2;
        if( query_temp("ly_hebi", target) )
        {
                damage2=(int)target->query_str()*(int)target->query_str()/10;
                attack2=(int)(target->query_skill("liangyi-sword",1)/5);
                delete_temp("ly_hebi", target);
                delete_temp("no_unwield", target);
                addn_temp("apply/attack", -attack2, target);
                addn_temp("apply/damage", -damage2, target);
                message_combatd(HIC"雙劍合璧完結，$N攻守恢復正常了。\n"NOR, target);
                return 1; 
        }
}
string name() {return replace_string(replace_string(PNAME,"「",""),"」","");}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"之"+name()+WHT"："NOR"\n");
        write(@HELP

        使用功效：
                兩個等級相近的人才可以使用，可加強攻擊次數。

        出手要求：
                玄天無極功100級
                兩儀劍有效100級
                最大內力 1000
                激發正兩儀劍法為招架技能
                激發正兩儀劍法為劍法技能
HELP
        );
        return 1;
}
