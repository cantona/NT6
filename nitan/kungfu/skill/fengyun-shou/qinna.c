// This program is a part of NITAN MudLIB
// qinna.c 擒拿

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "擒拿"; }

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("風雲手「擒拿」只能在戰鬥中對對手使用。\n");

        skill = me->query_skill("fengyun-shou", 1);

        if (skill < 120)
                return notify_fail("你的風雲手等級不夠，不會使用「擒拿」！\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真氣不夠，無法運用「擒拿」！\n");

        if (me->query_skill_mapped("hand") != "fengyun-shou")
                return notify_fail("你沒有激發風雲手，無法使用「擒拿」！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIC "$N" HIC "貼上前來，和$n" HIC "近身搏擊，只見$P"
              "的手忽折忽扭，或抓或甩，令人眼花繚亂！\n" NOR;

        ap = attack_power(me, "hand");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -80, me);
                damage = damage_power(me, "hand");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "$p" HIR "奮力抵抗，終究不敵$P"
                                           HIR "，連中數招後還是被壓制得無法"
                                           "反擊！\n" NOR);
                me->start_busy(1 + random(2));
                if (ap / 3 + random(ap) > dp && ! target->is_busy())
                        target->start_busy(random(2) + 3);
        } else
        {
                msg += CYN "可是$p" CYN "的看破了$P" CYN
                       "的招式，巧妙的一一拆解，沒露半點破綻！\n" NOR;
                addn("neili", -20, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
