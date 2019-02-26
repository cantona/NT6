#include <ansi.h>
#include <combat.h>

#define DAN "「" HIM "丹陽勁" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;

        if( userp(me) && !query("can_perform/miaojia-zhang/dan", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(DAN "只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用" DAN "。\n");         
                
        if ((int)me->query_skill("miaojia-zhang", 1) < 40)
                return notify_fail("你的苗家掌法不夠嫻熟，難以施展" DAN "。\n");

        if( query("max_neili", me)<200 )
                return notify_fail("你的內功修為不足，難以施展" DAN "。\n");

        if (me->query_skill_mapped("strike") != "miaojia-zhang")
                return notify_fail("你沒有激發苗家掌法，難以施展" DAN "。\n");

        if (me->query_skill_prepared("strike") != "miaojia-zhang")
                return notify_fail("你沒有準備苗家掌法，難以施展" DAN "。\n");

        if( query("neili", me)<50 )
                return notify_fail("你現在真氣太弱，難以施展" DAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIM "$N" HIM "凝聚內力，深深吸入一口氣，掌勁吞吐，對準$n"
              HIM "平平拍出。\n" NOR;
        addn("neili", -30, me);

        if (random(me->query_skill("force")) > target->query_skill("force") / 2)
        {
                me->start_busy(3);
                target->start_busy(random(3));
                
                damage = (int)me->query_skill("force", 1);
                damage = damage / 3 + random(damage / 3);
                
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
                                           HIR "$n" HIR "見勢連忙向後一縱，但卻只覺"
                                           "胸口一震，頓時兩耳轟鳴，已被$N" HIR "掌"
                                           "勁所傷！\n:內傷@?");
        } else 
        {
                me->start_busy(3);
                msg += CYN "可是$p" CYN "看破了$P"
                       CYN "的企圖，並沒有上當。\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}
