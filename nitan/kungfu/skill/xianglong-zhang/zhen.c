#include <ansi.h>
#include <combat.h>

#define ZHEN "「" HIW "震驚百里" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if( userp(me) && !query("can_perform/xianglong-zhang/zhen", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHEN "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(ZHEN "只能空手使用。\n");

        if ((int)me->query_skill("xianglong-zhang", 1) < 150)
                return notify_fail("你降龍十八掌火候不夠，難以施展" ZHEN "。\n");

        if (me->query_skill_mapped("strike") != "xianglong-zhang")
                return notify_fail("你沒有激發降龍十八掌，難以施展" ZHEN "。\n");

        if (me->query_skill_prepared("strike") != "xianglong-zhang")
                return notify_fail("你沒有準備降龍十八掌，難以施展" ZHEN "。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的內功修為不夠，難以施展" ZHEN "。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的內力修為不夠，難以施展" ZHEN "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不足，難以施展" ZHEN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = WHT "$N" WHT "施出降龍十八掌之「" HIW "震驚百里" NOR +
              WHT "」，全身真氣鼓動，雙掌如排山倒海般壓向$n" WHT "。\n"NOR;  

        ap=me->query_skill("strike")+query("str", me)*10;
        dp=target->query_skill("dodge")+query("dex", target)*10;

        if (ap / 2 + random(ap) > dp)
        { 
                damage = ap + random(ap / 2);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80,
                                           HIR "$n" HIR "只覺一股罡風湧至，根本不"
                                           "及躲避，$N" HIR "雙掌正中前胸，鮮血如"
                                           "箭般噴出。\n" NOR);
                addn("neili", -400, me);
                me->start_busy(3);
        } else
        {
                msg += CYN "$n" CYN "眼見$N" CYN "來勢洶湧，絲毫不"
                       "敢小覷，急忙閃在了一旁。\n" NOR;
                addn("neili", -200, me);
                me->start_busy(4);
        }
        message_combatd(msg, me, target);

        return 1;
}
