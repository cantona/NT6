// po.c 破字訣

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon, weapon2;
        int n;
        int skill, skill2, ap, dp, damage;
        string type;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        skill = me->query_skill("never-defeated", 1);

        skill2 = me->query_skill("martial-cognize", 1);

        if (! me->is_fighting(target))
                return notify_fail("破字訣只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("你必須手持兵刃才能施展破字訣！\n");

        type=query("skill_type", weapon);
        if (me->query_skill(type, 1) < 150)
                return notify_fail("你的" + to_chinese(type) + "水平有限，無法施展破字訣！\n");

        if (me->query_skill_mapped(type) != "never-defeated")
                return notify_fail("你沒有激發不敗神功，無法施展破字訣！\n");

        if (me->query_skill_mapped("force") != "never-defeated") 
                return notify_fail("你現在沒有激發不敗神功為內功，難以施展破字訣。\n");                 

        if (skill < 100)
                return notify_fail("你的不敗神功等級不夠，無法施展破字訣！\n");

        if( query("neili", me)<150 )
                return notify_fail("你現在真氣不夠！\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        addn("neili", -100, me);

        ap = attack_power(me, "force");
        dp = defense_power(target, "parry");

        msg = HIC "$N" HIC "手中" + weapon->name() +
              HIC "一抖，猶如夜雨流星，鋪天蓋地的攻向$n"
              HIC "，沒有半點規矩可循。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                n = 4 + random(4);
                if (ap * 2 / 3 + random(ap) > dp)
                {
                        msg += HIY "$n" HIY "見來招即巧又拙，不同於人間"
                               "任何招式，不禁大為慌亂，一時破綻迭出，$N"
                               HIY "見狀連出" + chinese_number(n) + "招！\n" NOR;
                        message_combatd(msg, me, target);
                        me->start_busy(1 + random(n));
                        while (n-- && me->is_fighting(target))
                        {
                                if (random(2) && ! target->is_busy())
                                        target->start_busy(1);
                                COMBAT_D->do_attack(me, target, weapon, 0);
                        }

                        weapon2=query_temp("weapon", target);
                        if( weapon2 && random(ap)>dp && query("type", weapon2) != "pin" )
                        {
                                msg = HIW "$n" HIW "覺得眼前眼花繚亂，手中的" + weapon2->name() +
                                      HIW "一時竟然拿捏不住，脱手而出！\n" NOR;
                                weapon2->move(environment(me));
                        } else
                        {
                                msg = HIY "$n竭力抵擋，一時間再也無力反擊。\n" NOR;
                        }

                        if (! me->is_fighting(target))
                                // Don't show the message
                                return 1;
                } else
                {
                        msg += HIY "$n" HIY "只辦了個勉力遮擋，全然無法反擊。\n" NOR;
                        target->start_busy(4 + random(skill / 30));
                }
        } else
        {
                msg += HIC "不過$n" HIC "一絲不苟，嚴守門户，沒有露出半點破綻。\n" NOR;
                me->start_busy(3 + random(2));
        }

        message_combatd(msg, me, target);
        return 1;
}
