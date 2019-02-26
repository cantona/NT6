// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "星光點點"; }

int perform(object me, object target)
{
        string msg;
        int i, ap, dp;

        i = me->query_skill("xingyi-zhang", 1)/5;
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「星光點點」只能在戰鬥中對對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("使用「星光點點」時雙手必須空着！\n");

        if( (int)me->query_skill("xingyi-zhang", 1) < 120 )
                return notify_fail("你的星移掌不夠嫻熟，不會使用「星光點點」。\n");

        if( (int)me->query_skill("shenyuan-gong", 1) < 120 )
                return notify_fail("你的神元功等級不夠，不能使用「星光點點」。\n");

        if( (int)me->query_dex() < 25 )
                return notify_fail("你的身法不夠強，不能使用「星光點點」。\n");

        if (me->query_skill_prepared("strike") != "xingyi-zhang"
                || me->query_skill_mapped("strike") != "xingyi-zhang")
                return notify_fail("你現在無法使用「星光點點」進行攻擊。\n");


        if( query("neili", me)<700 )
                return notify_fail("你現在內力太弱，不能使用「星光點點」。\n");

        addn("neili", -300, me);

        message_combatd(HIW "\n$N雙掌交相呼應,漫天的掌影猶如星星般在$n周圍閃爍不定！\n" NOR,me, target);

        addn_temp("apply/strengt", i, me);
        addn_temp("apply/attack", i, me);
        addn_temp("apply/unarmed_damage", i, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
        if( (int)me->query_str() >(int)target->query_str()/2)
        {
                addn_temp("apply/str", i, me);
                addn_temp("apply/attack", i, me);
                addn_temp("apply/damage", i, me);
                msg =  HIW"$N將神元神功發揮到極限，一雙手掌發出耀眼的光芒，幻化出漫天掌影！" NOR;
                message_combatd(msg, me, target);
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
                addn("neili", -100, me);
                addn_temp("apply/str", -i, me);
                addn_temp("apply/attack", -i, me);
                addn_temp("apply/damage", -i, me);
        }
        addn("neili", -400, me);
        addn_temp("apply/unarmed_damage", -i, me);
        addn_temp("apply/strengt", -i, me);
        addn_temp("apply/attack", -i, me);
        me->start_busy(1+random(2));
        return 1;
}
