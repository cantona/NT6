#include <ansi.h>
#include <combat.h>

string name() { return HIR "龍影掌" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int level;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((level = (int)me->query_skill("tie-zhang", 1)) < 100)
                return notify_fail("你鐵掌掌法火候不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "tie-zhang")
                return notify_fail("你沒有激發鐵掌掌法，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "tie-zhang")
                return notify_fail("你沒有準備鐵掌掌法，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功修為不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = WHT "$N" WHT "雙掌交錯，施出鐵掌絕技「" HIR "龍影掌" NOR +
              WHT "」，旋起層層殘影，籠罩$n" WHT "四方。\n" NOR;

        ap=attack_power(me,"strike")+me->query_str()*15;
        dp=defense_power(target,"parry")+target->query_dex()*15;

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "殘影晃動間$n" HIR "招式陡然一緊，竟被$N"
                       HIR "的掌招牽引得手忙腳亂！\n" NOR;
                target->start_busy(ap / 80 + 2);
                me->start_busy(1);
                addn("neili", -100, me);
        } else
        {
                msg += CYN "可是$n" CYN "看破了$N"
                       CYN "的企圖，鎮定解招，一絲不亂。\n" NOR;
                me->start_busy(2);
                addn("neili", -80, me);
        }
        message_combatd(msg, me, target);

        return 1;
}