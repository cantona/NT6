//hongtianza.c 奪命三斧之「轟天砸」
// Modified by Venus Oct.1997
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
    string msg,*limbs;
    int i,size,damage;
    object weapon;
    object my_w,target_w;
    my_w=query_temp("weapon", me);
//    target_w = target->query_temp("weapon");
    if( !target ) target = offensive_target(me);

              if( !target || !me->is_fighting(target) )
                      return notify_fail("「"HIM"「轟天砸」"NOR"」只能在戰鬥中對對手使用。\n");

              if( !objectp(weapon=query_temp("weapon", target)) )
                      return notify_fail("對方沒有使用兵器，難以施展「轟天砸」。\n");

    if( target->is_busy() )
    return notify_fail(target->name() + "目前正茫然不知所措，加緊攻擊吧。\n");
    if( (int)me->query_skill("duanyun-fu",1) < 50)
    return notify_fail("你目前功力還使不出「轟天砸」。\n");
    if( query("neili", me)<100 )
    return notify_fail("你的內力不夠。\n");
    addn("neili", -60, me);
msg = CYN"$N突然暴吼一聲：“我砸！我砸！我砸砸砸！”，手中巨斧竟然砸向$p手中兵刃！\n"NOR;
    target_w=query_temp("weapon", target);
    me->start_busy(1);

    if( query_temp("weapon", target) || 
   query_temp("secondary_weapon", target)){

    if( random(query("combat_exp", me)/100)>
      query("combat_exp", target)/300){
    if( target_w->weight() > 2 * random(my_w->weight()) ) {
msg+="結果$p手中的"+query("name", target_w)+"被$P的轟天砸砸個正着，再也把握不
住，立即脱手飛出！\n" NOR;
    target_w->unequip();
    target_w->move(environment(target));
    target->reset_action();
    target->start_busy( (int)me->query_skill("duanyun-fu") / 20 );
}
   msg += HIC
"只見$n手中的"+query("name", target_w)+"竟然被砸斷作數段，並且
受到$N的勁氣的激盪而向$n迅速射去！\n"NOR;
    message_combatd(msg,me,target);
    target_w->unequip();
    target_w->move(environment(target));
    set("name",query("name",  target_w)+"的碎片", target_w);
    set("value",query("value",  target_w)/10, target_w);
    set("weapon_prop", 0, target_w);
    target->reset_action();
    target->start_busy( (int)me->query_skill("duanyun-fu") / 20 );
    limbs=query("limbs", target);
    me->start_busy(1);
    msg += "結果$p呆立當場，被攻了個措手不及！\n" NOR;
    size=(int)(me->query_skill("duanyun-fu")/10);
    damage=random(size)+size;
                                 damage=damage+me->query_str()/3+random(query_temp("apply/damage",me)); 
    for(i=0;i<=random(size);i++)
   {
   msg =HIB"“嗤”，碎片射入$p"+limbs[random(sizeof(limbs))]+"！\n"NOR;
   message_combatd(msg,me,target);
   target->receive_damage("qi",damage,me);
   target->receive_wound("qi",damage/3,me);
   }
    COMBAT_D->report_status(target);
    } else {
    msg += "可是$p急忙將自己的兵刃閃開，並沒有讓$P的計謀得逞。\n" NOR;
    }
    return 1;
    }
    return notify_fail(target->name() + "目前是空手，你想砸什麼？\n");
}
