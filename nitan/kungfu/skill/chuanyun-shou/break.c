// break -「抱月摘星」
// Last Modify by sir 5/17/2001
 
#include <ansi.h>
#define PNAME "「抱月摘星」"
inherit F_SSERVER;
 
int perform(object me,object target)
{
        string msg;
        object weapon,  target_w;
        int ap, dp, equip;        
        object piece;
        int flag;
        string fskill,sskill,bskill,pfname,pskill;

        sskill = explode(__FILE__,"/")[<2];
        pfname = explode(__FILE__,"/")[<1][0..<3];

        if( !objectp(target) ) {flag =1;target = offensive_target(me);}
        
        if( !target || !target->is_character() || target == me ||        
                  !me->is_fighting(target) ||
          !living(target) || query_temp("noliving", target) )
                return notify_fail(PNAME"只能對戰鬥中的對手使用。\n");
 
//        if (objectp(weapon = me->query_temp("weapon")))
//                return notify_fail("你必須空手運功。\n");
        // 兵器空手均可

        fskill = "baiyun-xinfa";
        bskill = "hand";
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }
        if( (int)me->query_skill(fskill, 1) < 100 )
                return notify_fail("你的"+to_chinese(fskill)+"等級不夠, 不能使出"+PNAME+"。\n");

        if( (int)me->query_skill(sskill, 1) < 80 )
                return notify_fail("你的"+to_chinese(sskill)+"等級不夠, 不能使出"+PNAME+"。\n");

        if( query("neili", me)<800 )
                return notify_fail("你的內力不夠，無法運功！\n");
 
        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力修為不夠，無法運功！\n");
 
        msg = HIC"$N"HIC"沉肩滑步，自丹田中升起一股陰柔之氣順着血脈經絡傳至雙手勞宮穴，接着這股陰柔之氣就激射而出，噴向$n"HIC"手中的兵刃！\n"; 

        ap=query("combat_exp", me);
        dp=query("combat_exp", target)/2;
        if( dp < 1 ) dp = 1;
        target_w=query_temp("weapon", target);

        if( query_temp("weapon", target) || 
                query_temp("secondary_weapon", target) )
        { 
                if( random(ap) > dp )
                {        
                        addn("neili", -400, me);
                        msg += HIW"卻只聽得一陣丁當作響，兵器碎片丟了一地！\n"NOR;
                        target_w->unequip();
                        target->reset_action();
      seteuid(getuid());
      piece = new("/clone/misc/piece");
      set("long", "一堆兵器碎片。\n", piece);
      piece->set_name(query("name", target_w)+"的碎片",({query("id", target_w),"piece"}));
      piece->move(environment(target));
      destruct(target_w);
                        me->start_busy(random(2));
                }
                else 
                {
                        msg += "可是$p急急拆招，躲了開去。\n" NOR;
                        addn("neili", -200, me);
                        me->start_busy(2);
                }   
                message_combatd(msg, me, target);
                if(!target->is_fighting(me)) target->fight_ob(me);
                return 1;
        }
        return notify_fail(target->name() + "目前是空手，沒什麼可以震碎的。\n");
}

string name() {return replace_string(replace_string(PNAME,"「",""),"」","");}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"之"+name()+WHT"："NOR"\n");
        write(@HELP

        使用功效：
                毀壞對方兵器

        出手要求：
                白雲心法100級
                穿雲手80級
                內力1000
HELP
        );
        return 1;
}
