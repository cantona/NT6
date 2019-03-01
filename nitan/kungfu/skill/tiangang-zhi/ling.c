#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIC "凌空指穴" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你內功火候不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("tiangang-zhi") < 100)
                return notify_fail("你的天罡指穴法修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真氣現在不夠，難以施展" + name() + "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if (me->query_skill_mapped("finger") != "tiangang-zhi")
                return notify_fail("你沒有激發天罡指穴法，不能施展" + name() + "。\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIC "$N" HIC "使出天罡指穴法絕技「凌空指穴」，左手"
              "一連七指向著$n" HIC "胸前大穴接連戳出。\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "結果$p" HIR "不及攻敵，拼力躲避$P"
                       HIR "指力頓時動作大亂！\n" NOR;
                target->start_busy((int)me->query_skill("tiangang-zhi", 1) / 100 + 2);
                addn("neili", -100, me);
        } else
        {
                msg += CYN "$p" CYN "情急智生，奮力一躍，退出老遠。\n" NOR;
                me->start_busy(3);
                addn("neili", -30, me);
        }
        message_combatd(msg, me, target);

        return 1;
}
