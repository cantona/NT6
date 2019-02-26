//gladiator

#include <ansi.h>
#include <combat.h>

#define LEITING "「" HIR "雷霆霹靂" NOR "」" 

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int extra;
        object weapon;
        int damage;

        if( userp(me) && !query("can_perform/hongye-daofa/leiting", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n"); 


        if(me->is_busy())
                return notify_fail("你現在沒空！！\n");

        if( (int)me->query_skill("hongye-daofa",1) < 150)
                return notify_fail("你目前功力還使不出" LEITING "。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "blade" )
                        return notify_fail("你使用的武器不對。\n");

        if( query("neili", me)<500 )
                 return notify_fail("你的內力不夠。\n");

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail(LEITING "只能對戰鬥中的對手使用。\n");
  if (! living(target)) 
         return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n"); 

        weapon=query_temp("weapon", me);
        damage = me->query_skill("hongye-daofa", 1) + random((int)me->query_skill("dodge")) / 2;
        extra = me->query_skill("hongye-daofa",1) / 10;

        addn_temp("apply/attack", extra, me);
        addn_temp("apply/damage", extra, me);

        msg = HIR  "\n$N手中的"+ weapon->name() +HIR"幻出漫天刀雲，" + 
                   weapon->name() + 
              HIR  "劃破刀雲，雷霆霹靂般的擊向$n！\n" NOR;
        message_vision(msg, me, target);

        if (random(10) > 5)
        {
                msg = COMBAT_D->do_damage(me,target, WEAPON_ATTACK, damage, 10,
                       HIC  "\n$N刀氣好似暴雨前雷霆一般，夾雜着刺耳的尖鳴，直貫$n而去。\n" NOR);
                message_combatd(msg, me, target);
        } else
        {
                message_combatd(HIC  "\n$n不退反進，在$N揮刀之前逼到近身，使得$N不得不收回了七成的力道。\n" NOR, me, target);
                COMBAT_D->do_attack(me,target, weapon, TYPE_REGULAR, msg);
        }

        addn_temp("apply/attack", -extra, me);
        addn_temp("apply/damage", -extra, me);

        me->start_busy(1);
        return 1;
}