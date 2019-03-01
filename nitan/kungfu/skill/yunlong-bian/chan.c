#include <ansi.h>
#include <combat.h>

#define CHAN "「" HIW "纏字訣" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int ap, dp;

        /*
        if( userp(me) && !query("can_perform/yunlong-bian/chan", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");
        */
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(CHAN "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對，難以施展" CHAN "。\n");

        if ((int)me->query_skill("yunlong-bian",1) < 50)
                return notify_fail("你雲龍鞭法火候太淺，難以施展" CHAN "。\n");

        if (me->query_skill_mapped("whip") != "yunlong-bian")
                return notify_fail("你沒有激發雲龍鞭法，難以施展" CHAN "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if( query("neili", me)<50 )
                return notify_fail("你現在的真氣不足，難以施展" CHAN "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = WHT "$N" WHT "使出雲龍鞭法「纏」字訣，連揮" + weapon->name() +
              WHT"企圖把$n"  WHT "的全身纏住。\n" NOR;

        ap = attack_power(me, "whip");
        dp = defense_power(target, "parry");
        
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "結果$p" HIR "頓時被$P" HIR "的鞭勢牢牢纏住，"
                       "攻得措手不及！\n" NOR;
                target->start_busy((int)me->query_skill("whip") / 80 + 1);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的企圖，並沒有上"
                "當。\n" NOR;
        }
        addn("neili", -30, me);
        me->start_busy(2);
        message_combatd(msg, me, target);
        return 1;
}