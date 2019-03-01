#include <ansi.h>
#include <combat.h>

string name() { return HIC "影落飛花" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        mapping p;
        int i, af, lvl, count;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((lvl = (int)me->query_skill("lanhua-shou", 1)) < 140)
                return notify_fail("你蘭花拂穴手不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("hand") != "lanhua-shou")
                return notify_fail("你沒有激發蘭花拂穴手，難以施展" + name() + "。\n");

        if (! mapp(p = me->query_skill_prepare())
           || p["hand"] != "lanhua-shou")
                return notify_fail("你沒有準備蘭花拂穴手，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIC "$N" HIC "微一凝神，雙手作蘭花狀疾拂而出，一環環的勁氣登時直逼$n"
              HIC "全身各大要穴。\n" NOR;
        addn("neili", -150, me);

        ap = attack_power(me, "hand");

        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "頓時覺得眼花繚亂，全然分辨"
                       "不清真偽，只得拼命運動抵擋。\n" NOR;
                count = lvl / 5;
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIY "可是$n" HIY "凝神頓氣，奮力抵擋，絲"
                       "毫不受手影的幹擾，。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        af = member_array("hand", keys(p));

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;

                set_temp("action_flag", af, me);
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        me->start_busy(random(3));
        addn_temp("apply/attack", -count, me);
        return 1;
}
