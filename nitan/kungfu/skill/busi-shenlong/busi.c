// powerup.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if( target != me ) return notify_fail("你只能用不死神龍大法提升自己的戰鬥力。\n");

        if( (int)me->query_skill("busi-shenlong",1) < 50 )
          return notify_fail("你的內功火候還不夠，無法使用不死神龍大法！\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠!\n");
        if( query_temp("powerup", me) )
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("force");

        addn("neili", -100, me);

        message_combatd(
          HIR "$N雙目赤紅，縱聲大呼：洪教主神通護佑，眾弟子勇氣百倍，以一當百，以百當萬！\n"NOR, me);
        tell_object(me,HIW"你頓時感覺武功大進，勁力比先前大了數倍！\n" NOR);

        addn_temp("apply/attack", skill/3, me);
        addn_temp("apply/defense", skill/3, me);
        set_temp("powerup", 1, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill/3 :), skill);

        if( me->is_fighting() ) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/defense", -amount, me);
                delete_temp("powerup", me);
                tell_object(me, "你的不死神龍大法運行完畢，汗如泉湧，呼呼喘氣。\n");
        }
}