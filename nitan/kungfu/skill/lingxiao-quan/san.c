#include <ansi.h>
#include <combat.h>

string name() { return HIR "神倒鬼跌三連環" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int ap, dp, damage;
        string msg;
        object weapon;
        string wname;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("只有空手才能施展" + name() + "。\n");

        if (me->query_skill("force") < 250)
                return notify_fail("你的內功修為不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("lingxiao-quan", 1) < 180)
                return notify_fail("你的凌霄拳法不夠嫻熟，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("cuff") != "lingxiao-quan")
                return notify_fail("你沒有激發凌霄拳法，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("cuff") != "lingxiao-quan")
                return notify_fail("你現在沒有準備使用凌霄拳法，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        damage = damage_power(me, "cuff");
        ap = attack_power(me, "cuff");
        dp = defense_power(target, "parry");
        msg = HIR "$N" HIR "微微一笑，施出「神倒鬼跌三連環」，右手探出，直揪$n"
              HIR "後頸。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                           HIR "$P" HIR "出手既快，方位又奇，$p"
                                           HIR "如何避得，當即被$N" HIR "揪住，"
                                           "重重的摔在地上！\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "見勢不妙，急忙凝力穩住，右臂揮出，格開$P"
                       CYN "手臂。\n" NOR;
        }

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");
        msg += "\n" HIR "緊接着$N" HIR "“噫”的一聲，左手猛然探出，如閃電般抓向$n"
               HIR "的前胸。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45,
                                           HIR "$p" HIR "只覺胸口一麻，已被$P"
                                           HIR "抓住胸口，用力順勢一甩，頓時平"
                                           "平飛了出去！\n" NOR);
        } else
        {
                msg += CYN "可是$p" CYN "絲毫不為$P"
                       CYN "所動，奮力格擋，穩穩將這一招架開。\n" NOR;
        }

        attack_power(me, "cuff");
        dp = defense_power(target, "force");
        msg += "\n" HIR "又見$N" HIR "身子一矮，將力道聚於腿部，右腳猛掃$n"
               HIR "下盤，左腳隨着絆去。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "結果$p" HIR "稍不留神，頓時給$P"
                                           HIR "絆倒在地，嘔出一大口鮮血！\n" NOR);
        } else
        {
                msg += CYN "然而$p" CYN "沉身聚氣，穩住下盤，身子一幌，沒給$P"
                       CYN "絆倒。\n" NOR;
        }
        me->start_busy(2 + random(3));
        addn("neili", -200, me);
        message_combatd(msg, me, target);
        return 1;
}
