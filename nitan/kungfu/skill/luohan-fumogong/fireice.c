#include <ansi.h>

inherit F_CLEAN_UP;

#define FIREICE "「" HIW "冰" HIR "火" HIW "九重天" NOR "」"

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;
        string fam;
        fam=query("family/family_name", me);

        if( userp(me) && !query("skybook/item/xuanbingjiu", me) )
                 return notify_fail("你所學的內功中沒有這種功能。\n");

        if (target != me)
                return notify_fail("你只能用" FIREICE "來提升自己的戰鬥力。\n");

        if( query_temp("fireice", me) )
                return notify_fail("你現在正在施展" FIREICE "。\n");

        if ((int)me->query_skill("luohan-fumogong", 1) < 180)
                return notify_fail("你羅漢伏魔功火候不足，難以施展" FIREICE "。\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你的內力修為不足，難以施展" FIREICE "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的內力不足，難以施展" FIREICE "。\n");

        skill = me->query_skill("luohan-fumogong", 1);
        addn("neili", -300, me);
        me->receive_damage("qi", 0);

        message_combatd(HIC "$N" HIC "縱聲長嘯，運轉「" HIW "冰"
                        HIR "火" HIW "九重天" HIC "」真氣，聚力"
                        "于掌間，光華流動，煞為壯觀。\n" NOR, me);

        addn_temp("apply/unarmed_damage", skill*4, me);
        addn_temp("apply/damage", skill*4, me);
        addn_temp("apply/armor", skill*4, me);
        set_temp("fireice", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill * 4 :), skill);

        if (me->is_fighting())
                me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("fireice", me) )
        {
                addn_temp("apply/unarmed_damage", -amount, me);
                addn_temp("apply/damage", -amount, me);
                addn_temp("apply/armor", -amount, me);
                delete_temp("fireice", me);
                tell_object(me, "你的" FIREICE "運行完畢，將內力收回丹田。\n");
        }
}