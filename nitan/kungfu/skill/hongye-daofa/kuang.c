//kuang.c 
// gladiator

#include <ansi.h>
#include <combat.h>

#define KUANG "「" HIR "狂風落葉" NOR "」" 

inherit F_SSERVER;

int perform(object me, object target)
{
        int extra;
        object weapon;
        string msg;

        extra=me->query_skill("hongye-daofa",1);

        if( userp(me) && !query("can_perform/hongye-daofa/kuang", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if( !target ) target = offensive_target(me);

        if( !target||!target->is_character()||!me->is_fighting(target) )
                return notify_fail("你只能對戰鬥中的對手使用" KUANG "。\n");

        if( (int)me->query_skill("hongye-daofa",1) < 150)
                return notify_fail("你目前功力還使不出" KUANG "。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "blade" )
                        return notify_fail("你使用的武器不對。\n");

        if( query("neili", me)<800 )
                        return notify_fail("你的內力不夠。\n");
  if (! living(target)) 
         return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n"); 

        addn("neili", -300, me);
        msg = HIC "$N淡然一笑，本就快捷絕倫的刀法驟然變得更加凌厲！\n"
              HIC "就在這一瞬之間，$N已劈出二十一刀！刀夾雜着風，風裏含着刀影！\n"
              HIC "$n只覺得心跳都停止了！" NOR;

        message_vision(msg, me, target);                
        
        message_combatd(HIY  "$N從左面劈出七刀！" NOR, me, target); 
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR,msg);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR,msg);

        message_combatd(HIY  "$N緊跟$n從右面劈出七刀！" NOR, me, target); 
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR,msg);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR,msg);

        message_combatd(HIY  "$N竟然又從上面劈出七刀！" NOR, me, target);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR,msg);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR,msg);

        me->start_busy(2 + random(2));
        return 1;
}