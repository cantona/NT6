#include <ansi.h>
#include <combat.h>

string name() { return HIW "先天功" HIR "乾陽" HIY "劍氣" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int ap, dp, i, damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("xiantian-gong", 1) < 280)
                return notify_fail("你的先天功修為不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("sun-finger", 1) < 280)
                return notify_fail("你一陽指訣不夠嫻熟，難以施展" + name() + "。\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "xiantian-gong")
                return notify_fail("你沒有激發先天功為拳腳，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("你沒有激發先天功為內功，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("finger") != "sun-finger")
                return notify_fail("你沒有激發一陽指為指法，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "xiantian-gong"
           && me->query_skill_prepared("finger") != "sun-finger")
                return notify_fail("你沒有準備先天功和一陽指，難以施展" + name() + "。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "霎時只見$N" HIY "逆運" HIW "先天真氣" HIY "，化為" HIR
              "純陽內勁" HIY "聚於指尖，以一陽指訣手法疾點$n" HIY "全身諸"
              "多要穴。\n" NOR;

        ap = attack_power(me, "force") + me->query_skill("finger") +
             me->query_skill("unarmed");
        dp = defense_power(target, "force") + target->query_skill("dodge") +
             target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "force");
                damage = damage_power(me, "finger");
                damage+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 500,
                                           HIR "$n" HIR "只覺全身一熱，$P" HIR "「"
                                           HIW "先天功" HIR "乾陽" HIY "劍氣" HIR
                                           "」頓時破體而入，便似身置洪爐，噴出一口"
                                           "鮮血。\n" NOR);
                message_combatd(msg, me, target);
        } else
        {
                msg += CYN "$n" CYN "見$N" CYN "這指來勢洶湧，不敢"
                       "輕易招架，當即飛身縱躍閃開。\n" NOR;
                message_combatd(msg, me, target);
        }

        msg = HIR "緊接着$N" HIR "十指紛飛，接連彈出數道無形劍氣，$n" HIR "四面八"
              "方皆被劍氣所籠罩。\n"NOR;
        message_combatd(msg, me, target);

        addn_temp("apply/attack", ap/10, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }

        addn_temp("apply/attack", -ap/10, me);
        addn("neili", -600, me);
        me->start_busy(1 + random(3));
        return 1;
}
