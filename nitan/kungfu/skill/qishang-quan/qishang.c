// qishang 七傷
#include <ansi.h>

inherit F_SSERVER;

string name() { return "七傷"; }

int perform(object me, object target)
{
        string msg,str;
        object weapon;
        int i, j, damage;
        int ap, dp;

        if( !target ) target = me->select_opponent();

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("此招只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用此招！\n");

        if (me->query_skill_mapped("cuff") != "qishang-quan")
                return notify_fail("你沒有激發七傷拳為基本拳法的特殊技能，無法施展「七傷」。\n");

        if (me->query_skill_prepared("cuff") != "qishang-quan")
                return notify_fail("你沒有準備使用七傷拳，無法施展「七傷」。\n");

        if( (int)me->query_skill("qishang-quan", 1) < 250 )
                return notify_fail("你的七傷拳還不夠嫻熟，還沒有辦法拳出七傷。\n");

        if( (int)query("neili", me) < 800 )
                return notify_fail("以你的目前的內力沒有辦法發出這一招。\n");

        i = random((int)(me->query_skill("qishang-quan",1)/60));
        if( i < 1 ) i = 1;
        if( i > 7 ) i = 7;

        msg = HIY "$N凝神運功，使出“七傷拳”最後的絕招，"+chinese_number(i)+"股無比強勁的熱氣呼嘯的撲向$n身上各大要穴。\n"+
              HIC "$n急提丹田之氣與體內來回撞擊的"+chinese_number(i)+"股勁氣相擴。\n"NOR;

        addn("neili", -500, me);

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "force");

        if( ap /2 + random(ap) > dp || !living(target) )
        {
                me->start_busy(1);
                target->start_busy(i);

                damage = damage_power(me, "cuff");
                damage+= query("jiali", me);

                target->receive_damage("qi", (int)((i*(2*damage))/3), me);
                target->receive_wound("qi", (int)((i*damage)/3), me);

                msg += HIY"結果$n抵受不住$N的"+chinese_number(i)+"種勁氣在體內來回的撞擊。"+GRN"\n($n"+HIR"所受的內傷著實不輕。"+GRN")\n"NOR;
                str = COMBAT_D->status_msg((int)query("qi", target) * 100 /(int)query("max_qi", target));
                msg += "($n"+str+")\n";
        } else
        {
                me->start_busy(3);
                if (!target->is_busy()) target->start_busy(1);
                msg += CYN"可是$p忙運內力與$P的"+chinese_number(i)+"種勁氣相擴，把之在體內化之無形。\n"NOR;

        }
        message_combatd(msg, me, target);
        return 1;
}

/*
                                 破
                                  破破
                                   破破
                                   破破   破破破   
                    破破破破       破破破破   破破
               破破破破         破破破破     破破  
          破破破破         破破破  破破     破破 
       破破破    破破      破破    破破
                破破       破破    破破 
               破破         破破破破破破破破破
              破破          破破破         破破   
            破破破破破破    破破 破       破破 
          破破       破破   破破  破破   破破
        破破破        破破  破破   破破破破
      破破 破破      破破   破破     破破
    破破   破破     破破   破破    破破 破破
  破        破破破破破     破破   破破    破破
                         破破  破破         破破
                         破  破破             破破破 
                       破   破                 破破破
                     破
*/