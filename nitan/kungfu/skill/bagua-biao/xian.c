#include <ansi.h>
#include <combat.h>

#define XIAN "「" HIY "鏢中現掌" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object anqi;
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/bagua-biao/xian", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(XIAN "只能在戰鬥中對對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail(XIAN "只能空手施展。\n");

        if( !objectp(anqi=query_temp("handing", me) )
            || query("skill_type", anqi) != "throwing" )
                return notify_fail("你現在手中並沒有拿着暗器。\n");

        if (me->query_skill_mapped("strike") != "bagua-zhang") 
                return notify_fail("你沒有激發八卦掌，難以施展" XIAN "。\n");

        if (me->query_skill_prepared("strike") != "bagua-zhang") 
                return notify_fail("你沒有準備八卦掌，難以施展" XIAN "。\n");

        if (me->query_skill_mapped("throwing") != "bagua-biao") 
                return notify_fail("你沒有激發八卦鏢訣，難以施展" XIAN "。\n");

        if ((int)me->query_skill("bagua-zhang", 1) < 120)
                return notify_fail("你的八卦掌不夠嫻熟，難以施展" XIAN "。\n");

        if ((int)me->query_skill("bagua-biao", 1) < 120)
                return notify_fail("你的八卦鏢訣不夠嫻熟，難以施展" XIAN "。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，難以施展" XIAN "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你現在真氣不足，難以施展" XIAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "突然只聽$N" HIY "喝道：“$n" HIY "看招！”"
              "説完單手一揚，袖底頓時竄出一道金光，直射$n" HIY
              "而去！\n" NOR;

        ap = me->query_skill("strike", 1) +
             me->query_skill("throwing");

        dp = target->query_skill("dodge", 1) +
             target->query_skill("parry", 1);

        me->start_busy(3);
        if (anqi->query_amount() > 0)anqi->add_amount(-1);

        if (ap / 2 + random(ap) > dp)
        { 
                damage = damage_power(me, "throwing");
                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                           HIY "可只見$n" HIY "哈哈一笑，身子一矮"
                                           "，躲了過去。\n" NOR + HIR "哪知方才的"
                                           "暗器竟是虛招，等$p" HIR "反應時$N" HIR
                                           "已至跟前，雙掌齊施，重重的印在$n" HIR
                                           "胸前。\n" NOR);
        } else
        {
                msg += HIY "可是$p" HIY "看破了$P" HIY "的企圖，沒"
                       "有受到迷惑，招手將暗器全部攬了下來。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}