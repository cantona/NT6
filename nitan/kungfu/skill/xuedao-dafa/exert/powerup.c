#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount, int lv);

int exert(object me, object target)
{
        object weapon;
        int skill, lv;

        if (target != me)
                return notify_fail("你只能用血刀大法來提升自己的戰鬥力。\n");

        if( query("neili", me)<150 )
                return notify_fail("你的內力不夠。\n");

        if( query_temp("powerup", me) )
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("force");
        lv = me->query_skill("xuedao-dafa", 1) / 3;

        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(HIR "$N" HIR "仰天一聲狂哮，全身骨骼爆響，真氣盪漾，殺"
                        "氣彌漫，氣勢迫人。\n" NOR, me);

        if( objectp(weapon=query_temp("weapon", me)) && 
           query("skill_type", weapon) == "blade" && 
           me->query_skill_mapped("blade") == "xuedao-dafa")
        {
                message_combatd(HIR "$N" HIR "嗔目獰笑，手中" + weapon->name() +
                                HIR "頓時漾起一道血光，漫起無邊殺意。\n" NOR, me);
        }

        addn_temp("apply/attack", skill/3, me);
        addn_temp("apply/defense", skill/3, me);
        addn_temp("apply/damage", lv, me);
        set_temp("powerup", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill / 3, lv :), skill);
        if (me->is_fighting())
                me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount, int lv)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/defense", -amount, me);
                addn_temp("apply/damage", -lv, me);
                delete_temp("powerup", me);
                tell_object(me, "你的血刀大法運行完畢，將內力收回丹田。\n");
        }
}