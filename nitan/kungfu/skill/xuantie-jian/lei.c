// This program is a part of NITAN MudLIB
// lei.c 迅雷

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "迅雷"; }

int perform(object me, object target)
{
        string msg;
        int j, z;
        object weapon;

        j = me->query_skill("xuantie-jian", 1);
        z = me->query_skill("surge-force", 1);

        weapon=query_temp("weapon", me);

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「迅雷」只能在戰鬥中對對手使用。\n");

       if( !weapon || query("skill_type", weapon) != "sword" )
                return notify_fail("你必須在使用劍時才能使出「迅雷」！\n");

        if (me->query_skill_mapped("parry") != "xuantie-jian")
                return notify_fail("你的基本招架必須是玄鐵劍法時才能使出「迅雷」！\n");

        if(me->query_skill("xuantie-jian", 1) < 160 )
                return notify_fail("你的玄鐵劍法還不夠嫻熟，使不出「迅雷」。\n");

        if(me->query_skill("surge-force", 1) < 160 )
                return notify_fail("你的怒海狂濤修為不夠，使不出「迅雷」。\n");

        if( (int)me->query_skill("force", 1) < 200 )
                return notify_fail("你的內功等級不夠，使不出「迅雷」。\n");

        if( (int)me->query_str() < 32)
                return notify_fail("你的膂力還不夠，使不出「迅雷」。\n");

        if( (int)me->query_dex() < 30)
                return notify_fail("你的身法還不夠，使不出「迅雷」。\n");

        if( query("max_neili", me)<1800 )
                return notify_fail("你現在內力太弱，使不出「迅雷」。\n");

        if( query("neili", me)<900 )
                return notify_fail("你現在真氣太弱，使不出「迅雷」。\n");

        addn_temp("apply/str", z/6, me);
        addn_temp("apply/attack", j/6, me);
        addn_temp("apply/damage", z/2, me);

        msg = BLU "\n$N將手中的"+weapon->name()+"緩緩向$n一壓，忽然劍光一閃， 一劍幻為四劍，宛如奔雷掣電攻向$n！\n\n"NOR;
        message_combatd(msg, me, target);

        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));

        addn("neili", -500, me);

        addn_temp("apply/str", -z/6, me);
        addn_temp("apply/attack", -j/6, me);
        addn_temp("apply/damage", -z/2, me);

        me->start_busy(2);
        if( !target->is_busy() )
                target->start_busy(1);
        return 1;
}
