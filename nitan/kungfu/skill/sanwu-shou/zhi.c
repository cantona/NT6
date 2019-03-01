#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "無所不至" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time, level;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "whip" )
                return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");

        if ((level=me->query_skill("sanwu-shou", 1)) < 100)
                return notify_fail("你三無三不手不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("whip") != "sanwu-shou")
                return notify_fail("你沒有激發三無三不手，難以施展" + name() + "。\n");

        if( query("neili", me)<140 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIM "\n$N" HIM "長嘯一聲，騰空而起，施出絕招 「" HIW "無"
              "所不至" HIM "」，\n手中" + weapon->name() + HIM "化出無數"
              "光點，猶如滿天花雨般洒向$n全身各處" HIM "。" NOR;

        message_combatd(msg, me, target);

        ap = attack_power(me, "whip");
        dp = defense_power(target, "dodge");
        attack_time = 4;

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIR "結果$n" HIR "被$N" HIR "攻了個措手不及，$n"
                      HIR "慌忙招架，心中叫苦。\n" NOR;
                count = level / 5;
                attack_time += random(ap / 45);
                addn_temp("apply/attack", count, me);
        } else
        {
                msg= HIC "$n" HIC "見$N" HIC "這幾鞭招式凌厲，兇猛異"
                     "常，只得苦苦招架。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        if (attack_time > 7)
                attack_time = 7;

        addn("neili", -attack_time*20, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(4));

        return 1;
}