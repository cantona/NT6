// This program is a part of NITAN MudLIB
// freeze.c

#include <ansi.h>

inherit F_SSERVER; 

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

        if (me->query_skill("lengyue-shengong", 1) < 150)
                return notify_fail("你的冷月神功火候不夠，無法運用寒氣。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你的內力不夠!");

        msg = HIW "$N" HIW "默運冷月神功，一股寒氣迎面撲向$n"
              HIW "，四周登時雪花飄飄。\n" NOR;

        ap=attack_power(me, "force");
        dp=defense_power(target, "force");

        me->start_busy(2);

        if (ap / 2 + random(ap) > random(dp))
        {
                damage = damage_power(me, "force");
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                if( query("neili", target)>damage )
                        addn("neili", damage, target);
                else
                        set("neili", 0, target);

                msg += HIG "$n" HIG "忽然覺得一陣透骨寒意，霎時間"
                       "渾身的血液幾乎都要凝固了。\n" NOR;
                if (! target->is_busy()) target->start_busy(1);

                set_temp("lengyue-shengong_freeze", 1, target);
                target->start_call_out((: call_other, __FILE__, "remove_effect", target :),
                                       me->query_skill("lengyue-shengong") / 5);
        } else
                msg += HIY "$n" HIY "感到一陣寒意自心底泛起，連忙"
                       "運動抵抗，堪勘無事。\n" NOR;

        message_combatd(msg, me, target);

        return 1;
}

void remove_effect(object me)
{
        if ((int)query_temp("lengyue-shengong_freeze", me))
        {
                delete_temp("lengyue-shengong_freeze", me);
                tell_object(me, HIY "你感到身邊的寒氣漸漸散去了。\n" NOR);
        }
}

