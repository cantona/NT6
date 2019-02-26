#include <ansi.h>

inherit F_SSERVER;

string name() { return "九穹絕剎掌"; }

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

        if (! target || ! me->is_fighting(target))
                return notify_fail("「九穹絕剎掌」只能在戰鬥中對對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("「九穹絕剎掌」只能空手使用。\n");

        if( query("max_neili", me)<2200 )
                return notify_fail("你的內力修為還不夠，無法施展「九穹絕剎掌」。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠！\n");

        if ((int)me->query_skill("tie-zhang", 1) < 200)
                return notify_fail("你的鐵掌火候不夠，無法使用「九穹絕剎掌」！\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的內功修為不夠，無法使用「九穹絕剎掌」！\n");

        if (me->query_skill_mapped("strike") != "tie-zhang")
                return notify_fail("你沒有激發鐵掌掌法，難以施展「九穹絕剎掌」。\n");

        if (me->query_skill_prepared("strike") != "tie-zhang")
                return notify_fail("你現在沒有準備使用鐵掌掌法，難以施展「九穹絕剎掌」。\n");

        if (me->query_skill_prepared("cuff") == "tiexian-quan"
            || me->query_skill_prepared("unarmed") == "tiexian-quan" )
                return notify_fail("施展「九穹絕剎掌」時鐵掌掌法不宜和鐵線拳互背！\n");

        /*
        if ((string)me->query_skill_mapped("force") != "tianlei-shengong")
                return notify_fail("你必須激發天雷神功才能施展出「九穹絕剎掌」！\n");
        */

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIR "$N" HIR "一聲怒喝，猛然施出鐵掌掌法絕技「" NOR + WHT
              "九穹絕剎掌" NOR + HIR "」！體內天雷真氣急速運轉，雙臂陡"
              "然\n暴長數尺。只聽破空之聲驟響，雙掌幻出漫天掌影，鋪天"
              "蓋地向$n" HIR "連環拍出！\n\n" NOR;

        ap=attack_power(me,"strike")+me->query_str()*20;
        dp=defense_power(target,"parry")+target->query_dex()*20;
        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 3;
                msg += RED "$n" RED "面對$P" RED "這排山倒海攻勢，完全"
                       "無法抵擋，唯有退後。\n" NOR;
        } else
        {
                msg += HIC "$n" HIC "凝神應戰，竭盡所能化解$P" HIC "這"
                       "幾掌。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn_temp("apply/attack", count, me);
        addn_temp("apply/unarmed_damage", count, me);

        addn("neili", -300, me);
        for (i = 0; i < 6; i++)
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