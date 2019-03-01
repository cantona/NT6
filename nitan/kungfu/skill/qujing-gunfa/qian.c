#include <ansi.h>
#include <combat.h>

#define TUN "「" HIR "乾天無極" NOR "」"

inherit F_SSERVER;

void remove_effect(object me, int skill);

int perform(object me, object target)
{
        object weapon;
        int skill;
        string msg;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "club" )
                return notify_fail(TUN "你必須用棍法施展。\n");

        if( query_temp("qujing_qian", me) )
                return notify_fail(TUN "無法連續施展。\n");

        if ((int)me->query_skill("qujing-gunfa", 1) < 180)
                return notify_fail("你的乾天無極修為不夠，難以施展" TUN "。\n");

        if( query("max_neili", me)<2500 )
                return notify_fail("你的內力修為不足，難以施展" TUN "。\n");

        if (me->query_skill_mapped("club") != "qujing-gunfa")

                return notify_fail("你沒有激發取經棍法為棍法，難以施展" TUN "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不足，難以施展" TUN "。\n");


        msg = HIY "$N" HIY "雙手持刀，對天咆哮，所施正是乾天無極絕學「"
              HIR "乾天無極" HIY "」。\n霎時呼嘯聲大作，但見一股澎湃無比的罡勁"
              "至$N" HIY "刀間湧出，雲貫向$N" HIY "而去。\n" NOR;
        message_sort(msg, me);
        if (me->is_fighting())
                me->start_busy(2);
        skill = me->query_skill("qujing-gunfa",1);
        set_temp("qujing_qian", 1, me);
        addn_temp("apply/attack", skill*3/5, me);
        addn_temp("apply/defense", skill*2/5, me);
        addn_temp("apply/weapon_damage", skill/3, me);
        addn("neili", -600, me);
        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), skill);
        return 1;
}

void remove_effect(object me, int skill)
{
        if( query_temp("qujing_qian", me) )
        {
                addn_temp("apply/attack", -(skill*3/5), me);
                addn_temp("apply/defense", -(skill*2/5), me);
                addn_temp("apply/weapon_damage", -(skill/3), me);
                delete_temp("qujing_qian", me);
                tell_object(me, "你經過調氣養息，又可以繼續施展「" HIR "乾天無極" NOR "」了。\n");
        }
}

