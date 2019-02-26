// yi.c 百花錯易

#include <ansi.h>
#include <combat.h>

#define YI "「" HIW "百花錯易" NOR "」"

inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count;
        int i;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( userp(me) && !query("can_perform/baihua-cuoquan/yi", me) )
                return notify_fail("你還沒有受到高手指點，還不會運用" YI "。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(YI "只能對戰鬥中的對手使用。\n");
 
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(YI "只能空手施展。\n");
                
        if( query("max_neili", me)<3000 )
                return notify_fail("你的內力的修為不夠，現在無法使用" YI "。\n");

        if ((int)me->query_skill("force") < 280)
                return notify_fail("你的內功火候不足，無法使用" YI "。\n");

        if ((int)me->query_skill("baihua-cuoquan", 1) < 150)
                return notify_fail("你的百花錯拳火候不夠，無法使用" YI "。\n");

        if (me->query_skill_prepared("unarmed") != "baihua-cuoquan")
                return notify_fail("你現在沒有準備使用百花錯拳，無法使用" YI "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠，無法運用" YI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "大喝一聲，雙掌紛飛，擒拿手中夾着鷹爪功，左手查"
              "拳，右手綿掌。攻出去是\n八卦掌，收回時已是太極拳，諸家雜陳，"
              "毫無規律，鋪天蓋地向$n" HIW "狂湧而去。\n\n" NOR;

        ap = attack_power(me, "unarmed") + me->query_str();
        dp = defense_power(target, "parry") + target->query_dex();

        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 12;
                msg += HIR "$n" HIR "只見$P" HIR "運拳如奔，快拳繽紛遞出，"
                       "頓感頭暈目眩，不知該如何抵擋。\n" NOR;
        } else
        {
                msg += HIY "$n" HIY "只見$p" HIY "運拳如奔，快拳繽紛遞出，"
                       "連忙振作精神勉強抵擋。\n" NOR;
                count = 0;
        }

        message_vision(msg, me, target);
        addn_temp("apply/attack", count, me);

        addn("neili", -300, me);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(1 + random(6));
        addn_temp("apply/attack", -count, me);

        return 1;
}