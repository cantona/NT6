// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "破神訣" NOR; }

inherit F_SSERVER;

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

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("bahuang-gong", 1) < 220
                && (int)me->query_skill("beiming-shengong", 1) < 220)
                return notify_fail("你的本門火候不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("liuyang-zhang", 1) < 220)
                return notify_fail("你的天山六陽掌不夠嫻熟，難以施展" + name() + "。\n");

        if( query("max_neili", me)<3500 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "bahuang-gong"
                && me->query_skill_mapped("force") != "beiming-shengong")
                return notify_fail("你沒有激發本門內功，難以施展" + name() + "。\n");

        if( query("neili", me)<800 )
                return notify_fail("你現在真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIR "$N" HIR "將八荒六合唯我獨尊功提運至極限，全身真氣迸發，呼的一掌"
              "向$n" HIR "頭頂猛然貫落。\n" NOR;

        addn("neili", -500, me);
        ap = attack_power(me, "strike") + me->query_skill("force");
        dp = defense_power(target, "parry") + target->query_skill("force");

        if (target->is_good()) ap += ap / 10;

        if (ap / 2 + random(ap) > dp)
        {
                damage = 0;
                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        msg += HIR "頓時只聽“噗”的一聲，$N" HIR "一掌將$n"
                               HIR "頭骨拍得粉碎，腦漿四濺，當即癱了下去。\n"
                               NOR "( $n" RED "受傷過重，已經有如風中殘燭，"
                               "隨時都可能斷氣。" NOR ")\n";
                        damage = -1;
                } else
                {
                        damage = damage_power(me, "strike");
                        damage+= query("jiali", me);

                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 65,
                                                   HIR "$n" HIR "慌忙抵擋，可已然不及，$N"
                                                   HIR "掌勁如洪水般湧入體內，接連震斷數根"
                                                   "肋骨。\n:內傷@?");
                }
                me->start_busy(2);
        } else
        {
                msg += CYN "$p" CYN "見$P" CYN "掌勁澎湃，決計抵擋不"
                       "住，當即身子向後橫丈許，躲閃開來。\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        if (damage < 0)
                target->die(me);

        return 1;
}
