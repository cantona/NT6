// xiao.c 黯然銷魂

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIW "黯然銷魂" NOR; }

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
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手使用。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠！\n");

        if ((int)me->query_skill("sad-strike", 1) < 150)
                return notify_fail("你的黯然銷魂掌火候不夠，無法施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 320)
                return notify_fail("你的內功修為不夠，無法施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "sad-strike")
                return notify_fail("你現在沒有準備使用黯然銷魂掌，無法施展" + name() + "。\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIM "\n$N" HIM "一聲長吟：“黯然銷魂者，唯別而已矣！”，頓時心如"
              "止水，黯然神傷，\n於不經意中隨手使出了" HIR "『黯然銷魂』" HIM "！\n" NOR;

        ap = attack_power(me, "unarmed") +
             me->query_skill("force");

        dp = defense_power(target, "parry") +
             target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 10;
                msg += HIY "$n" HIY "見$P" HIY "這一招變化莫測，奇幻無"
                       "方，不由大吃一驚，慌亂中破綻迭出。\n" NOR;
        } else
        {
                msg += HIC "$n" HIC "不敢小覷$P" HIC
                       "的來招，騰挪躲閃，小心招架。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn_temp("apply/attack", count, me);
        addn_temp("apply/unarmed_damage", count, me);

        addn("neili", -400, me);
        for (i = 0; i < 8; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(2) && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(2 + random(5));
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/unarmed_damage", -count, me);

        return 1;
}
