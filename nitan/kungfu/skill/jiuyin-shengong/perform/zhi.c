// zhi.c 九陰神指

#include <ansi.h>

inherit F_SSERVER;

#define ZHI "「" HIY "九陰神指" NOR "」"

int perform(object me, object target)
{
        string msg;
        object weapon;
        int n;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        skill = me->query_skill("jiuyin-shengong", 1);

        if (! me->is_fighting(target))
                return notify_fail(ZHI "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail(ZHI "只能空手施展！\n");

        if (skill < 250)
                return notify_fail("你的九陰神功等級不夠，無法施展" ZHI "！\n");

        if( query("neili", me)<250 )
                return notify_fail("你現在真氣不夠，難以施展" ZHI "！\n");

//        if (me->query_skill_prepared("finger") != "jiuyin-shengong")
        if (me->query_skill_mapped("finger") != "jiuyin-shengong")
                return notify_fail("你沒有準備使用九陰神功，無法施展" ZHI "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        addn("neili", -100, me);

        ap = attack_power(me, "finger");
        dp = defense_power(target, "parry");

        msg = HIY "$N" HIY "出手成指，隨意點戳，似乎看盡了$n"
              HIY + "招式中的破綻。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                n = 4 + random(4);
                if (ap * 11 / 20 + random(ap) > dp)
                {
                        msg += HIY "$n" HIY "見來指玄幻無比，全然無法抵擋，慌亂之下破綻迭出，$N"
                               HIY "隨手連出" + chinese_number(n) + "指！\n" NOR;
                        message_combatd(msg, me, target);
                        me->start_busy(1 + random(n));
                        while (n-- && me->is_fighting(target))
                        {
                                if (random(2) && ! target->is_busy())
                                        target->start_busy(1);

                                COMBAT_D->do_attack(me, target, 0, 0);
                        }

                        weapon=query_temp("weapon", target);
                        if( weapon && random(ap)/2>dp && query("type", weapon) != "pin" )
                        {
                                msg = HIW "$n" HIW "覺得眼前眼花繚亂，手中的" + weapon->name() +
                                      HIW "一時竟然拿捏不住，脱手而出！\n" NOR;
                                weapon->move(environment(me));
                        } else
                        {
                                msg = HIY "$n勉力抵擋，一時間再也無力反擊。\n" NOR;
                        }

                        if (! me->is_fighting(target))
                                // Don't show the message
                                return 1;
                } else
                {
                        msg += HIY "$n" HIY "不及多想，連忙抵擋，全然無法反擊。\n" NOR;
                        if (! target->is_busy())
                                target->start_busy(4 + random(skill / 30));
                }
        } else
        {
                msg += HIC "不過$n" HIC "緊守門户，不露半點破綻。\n" NOR;
                me->start_busy(3 + random(2));
        }

        message_combatd(msg, me, target);
        return 1;
}