// This program is a part of NITAN MudLIB
// fei.c 魂魄飛揚

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "魂魄飛揚" NOR; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("qishang-quan", 1) < 160)
                return notify_fail("你的七傷拳不夠嫻熟，無法施展" + name() + "。\n");

        if ((int)me->query_skill("force", 1) < 160)
                return notify_fail("你的內功修為還不夠，無法施展" + name() + "\n");

        if (query("max_neili", me) < 2200)
                return notify_fail("你內力修為不足，無法施展" + name() + "\n");

        if ((int)query("neili", me) < 350)
                return notify_fail("你現在真氣不夠，無法施展" + name() + "。\n");

        if (me->query_skill_prepared("cuff") != "qishang-quan")
                return notify_fail("你沒有準備使用七傷拳，無法施展" + name() + "。\n");

        if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "\n$N" HIY "深吸一口起，將真氣運于雙拳之上，施出絕招「" HIR "魂魄飛揚" HIY
              "」，右拳平平一拳直出，\n但見普通一拳之中蘊涵了無窮的力量，拳未到風先至，猛然"
              "間襲向$n" HIY "。\n" NOR;

        ap = attack_power(me, "cuff") +
             me->query_skill("force");

        dp = defense_power(target, "parry") +
             target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "cuff");
                damage+= query("jiali", me);

                addn("neili", -320, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 120,
                                           HIR "只聽“砰”地一聲，$N" HIR "一拳正好打中$n" HIR "胸"
                                           "口，$n" HIR "怪叫一聲，吐出一口淤血！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "可是$p" HIC "奮力招架，硬生生的擋開了$P"
                       HIC "這一招。\n"NOR;
                addn("neili", -180, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
