//來去若無形 wuxing.c

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

//inherit F_CLEAN_UP;

void remove_effect(object me, int a_amount, int d_amount);

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int skill;
        int extra;
        string msg;
        
        if( userp(me) && !query("can_perform/luohan-jian/wuxing", me) )
                return notify_fail("你所使用的外功中沒有這樣的功能。\n");

        if ( !target ) target = offensive_target(me);

        if ( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("「來去若無形」只能在戰鬥中使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("「來去若無形」必須用劍才能施展。\n");

        if( (int)me->query_skill("luohan-jian", 1) < 120 )
                return notify_fail("你的「羅漢劍法」不夠嫻熟，不會使用「來去若無形」。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的內力不夠。\n");

        skill = me->query_skill("luohan-jian",1);

        extra = me->query_skill("luohan-jian",1) / 10;
        extra += me->query_skill("luohan-jian",1) / 10;
        addn_temp("apply/attack", extra, me);
        addn_temp("apply/damage", extra, me);

        msg = HIG "$N身行突變，瞬間猶如分出無數身影閃電般的向$n攻去！\n" NOR;
               message_vision(msg, me, target); 
        
        addn("neili", -200, me);
        
        message_combatd(HIR "  來字決！\n" NOR, me, target); 
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),
                                       TYPE_REGULAR); 

        message_combatd(HIY "    去字決！\n" NOR, me, target); 
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),
                                       TYPE_REGULAR); 

        message_combatd(HIG "      若字決！\n" NOR, me, target); 
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),
                                       TYPE_REGULAR); 
        
        message_combatd(HIB "        無字決！\n" NOR, me, target); 
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),
                                       TYPE_REGULAR); 
        
        message_combatd(HIW "          形字決！\n" NOR, me, target); 
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),
                                       TYPE_REGULAR); 

        msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, skill, 50, 
                    HIC "            來去若無形    幻化無真境 \n" NOR);
        message_combatd(msg, me, target); 

        me->start_busy(3);
        addn_temp("apply/attack", -extra, me);
        addn_temp("apply/damage", -extra, me);

        return 1;
}
