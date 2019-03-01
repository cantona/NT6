// xunlei.c 奔雷手絕招：迅雷不及掩耳
// By Alf

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
    int damage;
    string msg;

    if( !target ) target = offensive_target(me);

    if( !target || !target->is_character() || !me->is_fighting(target) )
   return notify_fail("「迅雷不及掩耳」只能對戰鬥中的對手使用。\n");

    if( (int)me->query_skill("yunlong-shengong", 1) < 100 )
   return notify_fail("你的雲龍神功火候尚淺，使不出「迅雷不及掩耳」。\n");

    if( (int)me->query_skill("benlei-shou", 1) < 100 )
   return notify_fail("你的奔雷手還不夠純熟，無法使出「迅雷不及掩耳」。\n");

    if( query("neili", me)<500 )
   return notify_fail("你的內力修為還不夠高。\n");

    msg = HIY "
$N突然大叱一聲，掌隨聲發，施展出「迅雷不及掩耳」，雙掌如排山倒海般攻向$n！\n"NOR;

    if( random(query("combat_exp", me)/100)>query("combat_exp", target)/300){
      me->start_busy(3);
   target->start_busy(random(3));

   damage = (int)me->query_skill("benlei-shou", 1)/2+(int)me->query_skill("unarmed",1)/3;

   damage = damage + random(damage);

   target->receive_damage("qi", damage);
   target->receive_wound("qi", damage/2);
   addn("neili", -300, me);
   msg += HIR"
$n躲避不及，被$N這一招擊得倒飛了出去，人在空中，口中已狂噴鮮血！\n"NOR;
    } else
    {
       me->start_busy(1);
       msg += HIG"$n大驚之下，足尖發力，身形向後急縱，險險避過了$P這一擊。\n"NOR;
    }
    message_combatd(msg, me, target);

    if(!target->is_fighting(me)) target->fight_ob(me);
    if(userp(target)) target->fight_ob(me);
    else if( !target->is_killing(me) ) target->kill_ob(me);
    return 1;
}

