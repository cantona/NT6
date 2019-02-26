#include <ansi.h>
#include <combat.h>

#define YIN "「" HIR "神卦天印" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;

        if( userp(me) && !query("can_perform/bazhen-zhang/yin", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(YIN "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(YIN "只能空手施展。\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("你的內功修為不夠，難以施展" YIN "。\n");

        if ((int)me->query_skill("bazhen-zhang", 1) < 130)
                return notify_fail("你的八陣八卦掌不夠嫻熟，難以施展" YIN "。\n");

        if (me->query_skill_mapped("strike") != "bazhen-zhang") 
                return notify_fail("你沒有激發八陣八卦掌，難以施展" YIN "。\n");

        if (me->query_skill_prepared("strike") != "bazhen-zhang") 
                return notify_fail("你沒有準備八陣八卦掌，難以施展" YIN "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在真氣不夠，難以施展" YIN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIR "$N" HIR "凝神沉履，積聚全身功力於一掌，攜着雷霆之勢奮力向$n"
              HIR "胸前拍落。\n" NOR;

        if (random(me->query_skill("strike")) > target->query_skill("parry") / 2)
        {
                me->start_busy(2);
                damage = me->query_skill("strike");
                damage = damage / 2 + random(damage);
                addn("neili", -250, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45,
                                           HIR "結果$p" HIR "招架不及，被$P" HIR
                                           "一掌印在胸口，接連斷了數根肋骨，噴出"
                                           "一大口鮮血！\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -100, me);
                msg += CYN "可是$p" CYN "奮力招架，不露半點破綻，將$P"
                       CYN "這一招驅之於無形。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}