#include <ansi.h>

inherit F_SSERVER;

string name() { return "雲霧暗點"; }

int perform(object me, object target)
{
        int ap, dp, damage;
        string msg;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( query_temp("weapon", me) )
                return notify_fail("你手上不能裝備任何東西。\n");

        if (! me->is_fighting(target))
                return notify_fail("只能對戰鬥中的對手使用。\n");

        if( (int)me->query_skill("boyun-suowu", 1) < 100 )
                return notify_fail("你的「撥雲鎖霧」不夠嫻熟，不能使用「雲霧暗點」。\n");

        if( (int)me->query_skill("biyun-xinfa",1) < 100)
                return notify_fail("你的心法不夠熟練！\n");

        if( query("neili", me)<800 )
                return notify_fail("你的內力不夠。\n");

        ap = attack_power(me, "hand") + me->query_dex()*10;
        dp = defense_power(target, "dodge") + target->query_dex()*10;

        msg = HIG "$N手腕一翻，信手一個拈花訣，內力暗吐，“嗤”的一聲，破空而去!\n"NOR;

        message_combatd(msg, me, target);

        addn("neili", -500, me);

        if (ap / 2 + random(ap) > dp)
        {
                if (! target->is_busy())
                        target->start_busy(ap/100 +2);
                msg = HIC "$n全身頓覺一麻，似乎不能動彈。\n"NOR;
        }
        else
                msg = HIM "只見$n側身一讓，一陣風聲，破空而過！\n"NOR;
        message_combatd(msg, me, target);

        return 1;
}
