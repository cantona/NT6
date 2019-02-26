#include <ansi.h>
#include <combat.h>

#define TONG "「" HIR "百鬼慟哭" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;

        if( userp(me) && !query("can_perform/zhenyu-quan/tong", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(TONG "只能對戰鬥中的對手使用。\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail(TONG "只能空手施展。\n");

        if ((int)me->query_skill("zhenyu-quan", 1) < 80)
                return notify_fail("你鎮獄拳法不夠嫻熟，難以施展" TONG "。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功修為不夠，難以施展" TONG "。\n");

        if (me->query_skill_mapped("cuff") != "zhenyu-quan") 
                return notify_fail("你沒有激發鎮獄拳法，難以施展" TONG "。\n");

        if (me->query_skill_prepared("cuff") != "zhenyu-quan")
                return notify_fail("你沒有準備鎮獄拳法，難以施展" TONG "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你現在的真氣不夠，難以施展" TONG "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIR "$N" HIR "隨手揮出一拳，飄忽不定的擊向$n" HIR "，看似竟不"
              "着半點力道。\n" NOR;

        if (random(me->query_skill("cuff")) > target->query_skill("dodge") / 2)
        {
                me->start_busy(2);
                damage = me->query_skill("cuff");
                damage = damage / 2 + random(damage / 2);
                addn("neili", -50, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 35,
                                           HIR "$n" HIR "只是隨手一擋，哪知$N" HIR
                                           "這拳後勢無窮，霎時拳勁吞吐，穿\n胸而過"
                                           "。$n" HIR "頓時嘔出幾大口鮮血，幾欲暈"
                                           "厥！\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -30, me);
                msg += CYN "可是$p" CYN "識破了$P"
                       CYN "招後更有殺着，當即向後躍開。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}