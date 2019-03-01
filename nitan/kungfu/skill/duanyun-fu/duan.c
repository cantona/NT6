//duan.c -奪命三斧之「斷雲斬」
// Modified by Venus Oct.1997
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
    int damage;
    string msg;
    if( !target ) target = offensive_target(me);
    if( !target||!target->is_character()||!me->is_fighting(target) )
    return notify_fail("你只能對戰鬥中的對手使用「斷雲斬」。\n");
    if( (int)me->query_skill("duanyun-fu",1) < 70)
    return notify_fail("你目前功力還使不出「斷雲斬」。\n");
    if( query("neili", me)<200 )
    return notify_fail("你的內力不夠。\n");
    addn("neili", -60, me);
msg = HIC"$N突然暴喝一聲，將手中巨斧斜向上舉起，然後在半空中劃出一
道圓弧，隨即徑直斜下斬向$n！這一瞬間，$n只覺得呼吸都停止了！\n"NOR;
    me->start_busy(1);

    if( random(query("combat_exp", me)/100)>
      query("combat_exp", target)/400){
    target->start_busy( (int)me->query_skill("duanyun-fu") / 20 );
    damage = (int)me->query_skill("duanyun-fu", 1)+(int)me->query_skill("axe", 1
)/2;
    damage = damage/2 + random(damage);

    target->receive_damage("qi", damage);
    target->receive_wound("qi", damage/2);
   msg += RED
"只見$n被$N一斧砍中，胸前裂開一道深深的傷口，血如箭般噴射而出！\n"NOR;
        message_combatd(msg, me, target);
        COMBAT_D->report_status(target);

    } else {
    msg += HIC "可是$p急忙抽身躲開，$P這招沒有得逞。\n" NOR;
    message_combatd(msg, me, target);
    }
    return 1;
}
