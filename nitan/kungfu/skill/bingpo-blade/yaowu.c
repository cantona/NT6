// modify by xiha@wmkj
// 神話世界﹒西遊記﹒版本４．５０
/* <SecCrypt CPL V3R05> */
 
#include <ansi.h>

inherit F_SSERVER;
string msg;
int perform(object me, object target)
{
        object weapon;
                
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要對誰施展這一招「妖霧沖天」?\n");
        weapon=query_temp("weapon", me);
        if(!me->is_fighting())
                return notify_fail("「妖霧沖天」只能在戰鬥中使用!\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力不夠！\n");

   if( query("neili", me)<500 )
     return notify_fail("你的內力不足！\n");


if( !weapon || query("skill_type", weapon) != "blade" )
    return notify_fail("你必須在使用兵器時才能使用！\n");

        if((int)me->query_skill("bingpo-blade",1) < 120)
        return notify_fail("你的冰魄寒刀等級還不夠!\n");

    msg = MAG
"\n$N陰陰一笑,手中的"+weapon->name()+""+MAG"輕輕一揮,登時飛沙走石,妖霧直沖天際!!\n"NOR;
message_vision(msg, me, target);
   delete("env/brief_message", me);
   delete("env/brief_message", target);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
         addn("force", -150, me);
//        target->apply_condition("bp_poison",5+random(5) + target->query_condition("bp_poison"));
        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
        }

        me->start_busy(1+random(1));
        return 1;
}