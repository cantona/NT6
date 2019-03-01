#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int i;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("井中八法只能對戰鬥中的對手使用。\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("手中沒刀還使什麼井中八法。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠！\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的內功火候不夠！\n");

        if ((int)me->query_skill("jingzhong-bafa", 1) < 200)
                return notify_fail("你的井中八法還不到家，無法施展絕招。\n");

        if (me->query_skill_mapped("blade") != "jingzhong-bafa")
                return notify_fail("你沒有激發井中八法，無法施展絕招。\n");

        msg = HIY "$N" HIY "一聲清嘯，手中的" + weapon->name() +
              HIY "將「井中八法」一齊施出，刀法變化莫測，籠罩了$n" HIY "周身要害！\n" NOR;

        if (random(me->query_skill("blade")) > target->query_skill("parry") / 3)
        {
                msg += HIR "$n" HIR "見來招實在是變幻莫測，不由得心"
                       "生懼意，招式登時出了破綻！\n" NOR;
                count = me->query_skill("jingzhong-bafa)", 1) / 3;
        } else
        {
                msg += HIC "$n" HIC "心底微微一驚，打起精神小心接招。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn("neili", -150, me);
        addn_temp("apply/attack", count, me);

        for (i = 0; i < 8; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(6));
        return 1;
}
