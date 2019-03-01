#include <ansi.h>

#define DIAN "「" HIW "鶴嘴勁點龍躍竅" NOR "」"

int exert(object me, object target)
{
        if( userp(me) && !query("can_perform/taiji-shengong/dian", me) )
                return notify_fail("你還沒有領悟到這個運功訣竅，無法施展" DIAN "。\n"); 

        if (! target)
                return notify_fail("你要用真氣為誰療傷？\n");

        if (target == me)
                return notify_fail(DIAN "只能對別人施展。\n");

        if (me->is_fighting() || target->is_fighting())
                return notify_fail("戰鬥中無法運功療傷。\n");

        if( query("not_living", target) )
                return notify_fail("你無法給" + target->name() + "療傷。\n");

        if ((int)me->query_skill("taiji-shengong", 1) < 100)
                return notify_fail("你的太極神功不夠嫻熟，難以施展" DIAN "。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力修為太淺，難以施展" DIAN "。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你現在的真氣不足，難以施展" DIAN "。\n");

        if( query("jing", me)<100 )
                return notify_fail("你現在精神狀態不佳，難以施展" DIAN "。\n");

        if( query("eff_qi", target) >= query("max_qi", target) && 
            query("eff_jing", target) >= query("max_jing", target) )
                return notify_fail("對方沒有受傷，不需要接受治療。\n");

        message_sort(HIW "\n只見$N" HIW "雙手食指和拇指虛拿，成鶴嘴勁"
                     "勢，以食指指尖點在$n" HIW "耳尖三分處的龍躍竅，"
                     "運起內功，微微擺動。這招鶴嘴勁點龍躍竅使將出來，"
                     "便是新斷氣之人也能還魂片刻。過得一會便見得$p額頭"
                     "上冒出豆大汗珠，頭上冒出隱隱白霧，哇的一下吐出瘀"
                     "血，臉色登時看起來紅潤多了。\n" NOR, me, target);

        addn("neili", -800, me);
        me->receive_damage("qi", 100);
        me->receive_damage("jing", 50);

        target->receive_curing("qi", 100 + (int)me->query_skill("force") +
                                     (int)me->query_skill("taiji-shengong", 1) * 3);

        if( query("qi", target) <= 0 )
                set("qi", 1, target);

        target->receive_curing("jing", 100 + (int)me->query_skill("force") / 3 +
                                       (int)me->query_skill("taiji-shengong", 1));

        if( query("jing", target) <= 0 )
                set("jing", 1, target);

        if (! living(target))
                target->revive();

        if (! target->is_busy())
                target->stary_busy(2);

        message_vision("\n$N閉目冥坐，開始運功調息。\n", me);
        me->start_busy(10);
        return 1;
}
