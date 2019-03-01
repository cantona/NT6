// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "封字訣" NOR; }

int perform(object me, object target)
{
        object weapon;
        string wp;
        int skill;

        if (! target) target = offensive_target(me);

        if( query_temp("feng_zijue", me) )
                return notify_fail("你現在正在施展" + name() + "。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        skill = me->query_skill("dagou-bang", 1);

        if (skill < 120)
                return notify_fail("你打狗棒法不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("staff") != "dagou-bang")
                return notify_fail("你沒有激發打狗棒法，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("你的內功火候不足，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        wp = weapon->name();

        message_combatd(HIG "$N" HIG "使出打狗棒法「" HIY "封"
                        HIG "」字訣，手中" + wp + HIG "疾速舞"
                        "動，幻出許許棒影護住周身。\n" NOR, me);

        addn("neili", -150, me);
        addn_temp("apply/defense", skill/3, me);
        set_temp("feng_zijue", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill / 3 :), skill / 2);

        if (me->is_fighting())
                me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("feng_zijue", me) )
        {
                addn_temp("apply/defense", -amount, me);
                delete_temp("feng_zijue", me);
                tell_object(me, "你的" + name() + "施展完畢，將內力收回丹田。\n");
        }
}
