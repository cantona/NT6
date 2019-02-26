#include <ansi.h>
#include <combat.h>

#define FAN "「" HIW "翻卦連環掌" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int count;
        int lvl;
        int i;

        if( userp(me) && !query("can_perform/youshen-zhang/fan", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(FAN "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(FAN "只能空手施展。\n");

        if ((int)me->query_skill("force") < 160)
                return notify_fail("你的內功修為不夠，難以施展" FAN "。\n");

        if ((lvl = (int)me->query_skill("youshen-zhang", 1)) < 120)
                return notify_fail("你的遊身八卦掌不夠嫻熟，難以施展" FAN "。\n");

        if (me->query_skill_mapped("unarmed") != "youshen-zhang")
                return notify_fail("你沒有激發遊身八卦掌，難以施展" FAN "。\n");

        if (me->query_skill_prepared("unarmed") != "youshen-zhang")
                return notify_fail("你沒有準備遊身八卦掌，難以施展" FAN "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在真氣不夠，難以施展" FAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "只見$N" HIW "腳踏八卦四方之位，身形在全場遊走不定，雙掌隨後緊"
              "拍而出，緊緊纏繞着$n" HIW "。\n" NOR;
        addn("neili", -150, me);

        if (random(me->query_skill("force") + me->query_skill("bazhen-zhang")) >
            target->query_skill("force"))
        {
                msg += HIR "$n" HIR "頓時覺得呼吸不暢，全然被$N"
                       HIR "這股奇怪的力道所制，只得拼命運動抵擋"
                       "。\n" NOR;
                count = lvl / 5;
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIC "$n" HIC "深吸一口氣，凝神抵擋，但見"
                       "周圍$N" HIC "掌影重重，$p" HIC "卻是臨危"
                       "不亂，鎮定拆招。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        me->start_busy(1 + random(6));
        addn_temp("apply/attack", -count, me);
        return 1;
}