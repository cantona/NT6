#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int ap;
        int dp;
        int damage;
        string msg;

        if (target == me || ! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("你只能用寒氣攻擊戰鬥中的對手。\n");

        if (me->query_skill("bingxin-jue", 1) < 150)
                return notify_fail("你的冰心決火候不夠，無法運用寒氣。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你的內力不夠!");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "默運冰心決，一股寒氣迎面撲向$n"
              HIW "，四周登時雪花飄飄。\n" NOR;

        ap = me->query_skill("force");
        dp = me->query_skill("force");

        me->start_busy(2);

        if (ap / 2 + random(ap) > random(dp))
        {
                damage = ap / 3 + random(ap / 3);
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage, me);
                if( query("neili", target)>damage )
                        addn("neili", damage, target);
                else
                        set("neili", 0, target);

                msg += HIR "$n" HIR "忽然覺得一陣透骨寒意，霎時間"
                       "渾身的血液幾乎都要凝固了。\n" NOR;
                target->start_busy(1);
        } else
                msg += HIY "$n" HIY "感到一陣寒意自心底泛起，連忙"
                       "運動抵抗，堪勘無事。\n" NOR;

        message_combatd(msg, me, target);

        return 1;
}