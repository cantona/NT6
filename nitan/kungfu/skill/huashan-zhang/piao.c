
#include <ansi.h>
#include <combat.h>

string name() { return HIG "飛絮飄渺" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧！\n");

        if ((int)me->query_skill("huashan-zhang", 1) < 30)
                return notify_fail("你的華山掌法不夠嫻熟，不會使用" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "huashan-zhang")
                return notify_fail("你沒有準備使用華山掌法，無法施展" + name() + "。\n");

        if( query("neili", me)<60 )
                return notify_fail("你現在真氣不夠，無法施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIM "\n猛然間$N" HIM "雙掌不斷拍向$n" HIM "出，風聲呼呼，攻到途中忽又左\n"
              "手虛出右手作勢欲發，虛虛實實，飄渺不定，正是華山絕招「" HIG  "飛絮飄渺" HIM
              "」。 \n頃刻劍$n" HIM "已被$N" HIM "掌風籠罩。\n" NOR;

        addn("neili", -30, me);
        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "結果$p" HIR "一時無法辨別其中虛實，竟無法施招。\n" NOR;
                target->start_busy(ap / 100 + 2);
        } else
        {
                msg += CYN "可是$n" CYN "看破其中虛實，更不理會。\n" NOR;
                me->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}