// baigu.c 白骨森然

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "白骨森然"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int damage;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("辣手化骨只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，無法施展化骨掌。\n");

        if ((int)me->query_skill("huagu-mianzhang", 1) < 100)
                return notify_fail("你的化骨綿掌還不夠嫻熟，不會化骨掌。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠，不能化骨。\n");

        if (me->query_skill_mapped("strike") != "huagu-mianzhang")
                return notify_fail("你沒有激發化骨綿掌，無法施展化骨掌。\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        addn("neili", -100, me);

        msg = BLU "$N"BLU"面無表情，驀然遊身而上，繞着$n"BLU"疾轉數圈，猛地身形一縮，轉到$n"BLU"身前，\n"
              "右手劃出一道光圈，往$n"BLU"丹田印了下去！\n"NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if( ap / 2 + random(ap) > dp )
        {
                me->start_busy(2);
                if( !target->is_busy() )
                        target->start_busy(random(3));
                damage=query("neili", target)/2;
                if (damage < 300) damage = 300;

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                          CYN"$n"CYN"匆忙閃身，卻已不及，只覺渾身真氣難聚，人如軟泥般向後癱倒！\n"NOR);
        } else
        {
                me->start_busy(2);
                msg += HIY"可是$p也隨着縱身斜躍，避開了丹田要害。\n"NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}
