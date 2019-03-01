// qixing. 七星絕命劍

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon=query_temp("weapon", me);
        int damage;

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("七星絕命劍只能對戰鬥中的對手使用。\n");

    if( (int)me->query_skill("quanzhen-jianfa", 1) < 90 )
                return notify_fail("你的全真劍法不夠熟練，使不出七星絕命劍。\n");
  
    if( !weapon || query("skill_type", weapon) != "sword"
        || me->query_skill_mapped("sword") != "quanzhen-jianfa")
                return notify_fail("你現在無法使用七星絕命劍。\n");

    if( query("neili", me)<200 )
                return notify_fail("你的內力不夠，無法使用七星絕命劍。\n");

         msg = MAG "$N一聲長嘯，一抖手中劍，頓時形成一道劍幕，狂風暴雨般壓向$n。就在
$n慌亂之間，劍幕中飛出七朵寒星，如流星般射向$n。\n";

        if( random(query("combat_exp", me))>query("combat_exp", target)/3){
                msg += "$n躲閃不及，已然中劍！\n";
                damage = 3*(int)me->query_skill("quanzhen-jianfa", 1);
                damage = damage / 2 + random(damage / 2);
                if( damage>query("neili", target)/10 )
                        damage-=query("neili", target)/15;
                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/3);
                 if( damage < 40 ) msg += HIY"$n已身中數劍，身上到處是血。\n"NOR;
                 else if( damage < 80 ) msg += HIR"$n身中七劍，鮮血狂噴而出！\n"NOR;
                 else msg += RED"$n“哇”的狂叫一聲，身上噴出七道血劍！\n"NOR;
                message_vision(msg, me, target);
        } 
        else {
                 msg += HIW"$n情急之中向後激飛，隨機趴下，堪堪躲過了這致命一擊。\n" NOR;
                message_vision(msg, me, target);
        }
        addn("neili", -180, me);
        me->start_busy(2);

        return 1;
}
