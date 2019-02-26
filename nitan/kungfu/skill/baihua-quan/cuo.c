#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int count;
        int lvl;
        int i;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("百花錯亂只能對戰鬥中的對手使用。\n");

        if (me->query_skill_prepared("unarmed") != "baihua-quan" &&
            me->query_skill_prepared("cuff") != "baihua-quan" &&
            me->query_skill_prepared("strike") != "baihua-quan" &&
            me->query_skill_prepared("claw") != "baihua-quan" &&
            me->query_skill_prepared("hand") != "baihua-quan")
                return notify_fail("你現在沒有準備使用百花錯拳，無法施展百花錯亂！\n");
 
        if( query_temp("weapon", me) )
                return notify_fail("百花錯亂須是空手才能施展。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠，無法施展百花錯亂。\n");

        if ((lvl = me->query_skill("baihua-quan", 1)) < 160)
                return notify_fail("你的百花錯拳還不夠純熟！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "只見$N使出百花錯拳的精妙百花錯亂，擒拿手中夾着鷹爪功，左手查拳，右手綿掌。攻\n"
                  "出去是八卦掌，收回時已是太極拳，諸家雜陳，毫無規律，只令$n眼花繚亂。\n\n" NOR;
        i = 10;
        if (lvl * 2 / 3 - random(lvl) > (int)target->query_skill("parry") / 2)
        {
                msg += HIW "$n只感到頭暈目眩，只見$N或掌、或爪、或拳、或指鋪天蓋地的向自己各個部位襲來！\n"
                           "只一瞬間，全身竟已多了數十出傷痕，"NOR+HIR"鮮血"NOR+HIW"狂瀉不止！\n"NOR;
                count = me->query_skill("baihua-quan", 1) / 6;
                addn_temp("apply/attack", count, me);
                i += random(5);
        } else
        {
                msg += HIY "$n只見$N運拳如奔，快拳繽紛遞出，連忙振作精神勉強抵擋。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn("neili", -300, me);

        while (i--)
        {
                if (! me->is_fighting(target))
                        break;
                if (i > 5 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(6));
        return 1;
}
