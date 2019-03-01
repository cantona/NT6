#include <ansi.h>
#include <combat.h>

string name() { return HIR "掌心雷" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("tie-zhang", 1) < 160)
                return notify_fail("你鐵掌掌法火候不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "tie-zhang")
                return notify_fail("你沒有激發鐵掌掌法，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "tie-zhang")
                return notify_fail("你沒有準備鐵掌掌法，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 240)
                return notify_fail("你的內功修為不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<2500 )
                return notify_fail("你的內力修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = WHT "$N" WHT "運轉真氣施出「" HIR "掌心雷" NOR +
              WHT "」絕技，雙掌翻紅，有如火燒，朝$n" WHT "猛"
              "然拍出。\n" NOR;

        ap=attack_power(me,"strike")+me->query_str()*10;
        dp=defense_power(target,"parry")+target->query_con()*10;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me,"strike");
                damage+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 85,
                                           HIR "結果只聽$n" HIR "一聲悶哼，被$N"
                                           HIR "一掌劈個正著，口中鮮血狂噴而出。"
                                           "\n" NOR);
                addn("neili", -250, me);
                me->start_busy(2);
        } else
        {
                msg += CYN "$n" CYN "眼見$N" CYN "來勢洶湧，絲毫"
                       "不敢小覷，急忙閃在了一旁。\n" NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}