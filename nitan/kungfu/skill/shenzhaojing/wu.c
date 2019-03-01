#include <ansi.h>
#include <combat.h>

#define WU "「" HIR "無影拳舞" NOR "」"

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

        if( userp(me) && !query("can_perform/shenzhaojing/wu", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(WU "只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能施展" WU "。\n");

        if (me->query_skill_mapped("unarmed") != "shenzhaojing")
                return notify_fail("你沒有激發神照經神功為空手技能，無法施展" WU "。\n");

        if (me->query_skill_prepared("unarmed") != "shenzhaojing")
                return notify_fail("你現在沒有準備使用神照經神功，無法施展" WU "。\n");

        if ((int)me->query_skill("shenzhaojing", 1) < 200)
                return notify_fail("你的神照經神功火候不夠，無法施展" WU "。\n");

        if ((int)me->query_skill("unarmed", 1) < 200)
                return notify_fail("你的基本拳腳火候不夠，無法施展" WU "。\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的內力修為不足，無法施展" WU "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠，無法施展" WU "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIR "$N" HIR "一聲暴喝，將神照功功力聚之于拳，攜著雷霆萬"
              "鈞之勢向連環$n" HIR "攻出。\n"NOR;

        ap=me->query_skill("force")+query("con", me)*10;
        dp=target->query_skill("dodge")+query("dex", target)*10;

        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 10;
                msg += HIR "$n" HIR "面對$P" HIR "這排山倒海的攻"
                       "勢，不禁心生懼意，慌亂中破綻迭出。\n" NOR;
        } else
        {
                msg += HIC "$n" HIC "微一凝神，面對$P" HIC "這排"
                       "山倒海的攻勢卻絲毫不亂，小心招架。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn_temp("apply/attack", count, me);

        addn("neili", -200, me);
        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 0 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(1 + random(5));
        addn_temp("apply/attack", -count, me);

        return 1;
}
