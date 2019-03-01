// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "圓滿勢" NOR; }

inherit F_SSERVER;

void remove_effect(object me, int amount);

int perform(object me)
{
        object weapon;
        string wp;
        int skill;

        if( query_temp("yuan_man", me) )
                return notify_fail("你現在正在施展" + name() + "。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "hammer" )
                return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("hammer") != "riyue-lun")
                return notify_fail("你沒有激發日月輪法，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "longxiang-gong")
                return notify_fail("你沒有激發龍象般若功，難以施展" + name() + "。\n");

        if ((int)me->query_skill("riyue-lun", 1) < 120)
                return notify_fail("你的日月輪法火候不足，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("你的內功火候不足，難以施展" + name() + "。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        wp = weapon->name();

        message_combatd(HIY "$N" HIY "吐氣揚聲，施出日月輪法「" HIW "圓滿勢"
                        HIY "」，手中" + wp + HIY "運轉如飛，迅速護住周身要"
                        "害。\n" NOR, me);

        skill = me->query_skill("riyue-lun", 1);

        addn("neili", -200, me);
        addn_temp("apply/defense", skill/3, me);
        set_temp("yuan_man", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill / 3 :), skill / 2);

        if (me->is_fighting())
                me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("yuan_man", me) )
        {
                addn_temp("apply/defense", -amount, me);
                delete_temp("yuan_man", me);
                tell_object(me, "你的" + name() + "運行完畢，將內力收回丹田。\n");
        }
}

