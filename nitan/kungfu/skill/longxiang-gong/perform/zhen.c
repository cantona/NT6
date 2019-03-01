// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "真﹒般若極" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp;
        int damage;
        int i, count;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("longxiang-gong", 1) < 390)
                return notify_fail("你的龍象般若功修為不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<7000 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "longxiang-gong")
                return notify_fail("你沒有激發龍象般若功為拳腳，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "longxiang-gong")
                return notify_fail("你沒有激發龍象般若功為內功，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "longxiang-gong")
                return notify_fail("你沒有準備使用龍象般若功，難以施展" + name() + "。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "仰天一聲怒嚎，將龍象般若功提運至極限，全身頓時罡勁"
              "迸發，真氣蒸騰而出，籠罩$N" HIY "\n四方！電光火石間，$N" HIY "雙"
              "拳已攜著雷霆萬鈞之勢崩擊而出，卷起萬裡塵埃，正是密宗絕學：\n" NOR;

        msg += HIW
        "        般      般般般           若        若           極    極極極極極極\n"
        "    般般般般    般  般       若若若若若若若若若若       極       極    極\n"
        "    般    般    般  般           若        若       極極極極極  極    極\n"
        "    般 般 般 般般    般般          若                 極極極  極極極 極極極\n"
        "  般般般般般般             若若若若若若若若若若若若  極 極 極  極極     極\n"
        "    般    般   般般般般         若                   極 極 極  極 極   極\n"
        "    般 般 般    般  般        若 若若若若若若若      極 極 極 極   極極\n"
        "    般    般     般般       若   若          若         極   極     極\n"
        "   般    般   般般  般般         若若若若若若若         極  極  極極極極極\n\n" NOR;

        msg += HIY "$N" HIY "一道掌力打出，接著便湧出了第二道、第三道掌力，掌勢"
               "連綿不絕，氣勢如虹！直到$N" HIY "\n第十三道掌力打完，四周所籠罩"
               "著的罡勁方才慢慢消退！而$n" HIY "此時卻已是避無可避！\n\n" NOR;

        ap = attack_power(me, "unarmed") + me->query_con()*10;
        dp = defense_power(target, "parry") + target->query_dex()*10;

        if (ap / 2 + random(ap) > dp)
        {
                if (! userp(target) ||
                    query("max_neili",me) / 2 + random(query("max_neili",me) / 2) > query("max_neili",target) * 5/4) 
                {
                        msg += HIR "$n" HIR "全然無力阻擋，竟被$N"
                                HIR "一拳擊得飛起，重重的跌落在地上。\n" NOR;
                        addn("neili", -50, me);
                        me->start_busy(1);

                        message_combatd(msg, me, target);
                        target->receive_damage("qi", 100, me);
                        target->unconcious(me);

                        me->start_busy(1);
                        return 1;
                } else
                {
                        damage = damage_power(me, "unarmed");
                        damage+= query("jiali", me);
                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 200,
                                                   HIR "$n" HIR "不及閃避，頓被$N" HIR
                                HIR "一拳擊得飛起，重重的跌落在地上。\n" NOR);
                        count = ap / 10;
                        msg += HIR "$n" HIR "被$p" HIR "罡勁所逼，一時無力作出抵擋，竟呆立當場。\n" NOR;
                }
        } else
        {
                msg += HIY "$n" HIY "見$p" HIY "來勢迅猛之極，甚難防備，連"
                       "忙振作精神，小心抵擋。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn_temp("apply/attack", count, me);
        addn_temp("apply/unarmed_damage", count, me);

        addn("neili", -300, me);

        for (i = 0; i < 8; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(1 + random(3));
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/unarmed_damage", -count, me);

        return 1;
}
