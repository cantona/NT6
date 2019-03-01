#include <ansi.h>
#include <combat.h>

string name() { return HIC "風雲變幻" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int count, ap, dp;
        int lvl;
        int i;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((lvl = (int)me->query_skill("wuluo-zhang", 1)) < 100)
                return notify_fail("你五羅輕煙掌不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "wuluo-zhang")
                return notify_fail("你沒有激發五羅輕煙掌，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "wuluo-zhang")
                return notify_fail("你沒有準備五羅輕煙掌，難以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIC "$N" HIC "施出五羅輕煙掌絕技，單掌輕輕一抖，登時化出五道掌"
              "影，輕飄飄向$n" HIC "拍去。\n" NOR;
        addn("neili", -50, me);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "頓時覺得眼花繚亂，全然分辨"
                       "不清真偽，只得拼命運動抵擋。\n" NOR;
                count = lvl / 10;
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIC "可是$n" HIC "凝神頓氣，奮力抵擋，絲"
                       "毫不受掌影的幹擾，。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        me->start_busy(1 + random(5));
        addn_temp("apply/attack", -count, me);
        return 1;
}