// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "寰陽式" NOR; }

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

        if (me->query_skill("force") < 200)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("liuyang-zhang", 1) < 130)
                return notify_fail("你的天山六陽掌不夠嫻熟，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIR "$N" HIR "雙掌一振，施出天山六陽掌「寰陽式」，幻出"
              "滿天掌影，團團罩住$n" HIR "。\n" NOR;

        addn("neili", -50, me);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                damage+= query("jiali", me);
                addn("neili", -200, me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 65,
                                           HIR "$n" HIR "見躲閃不得，只能硬擋下一"
                                           "招，頓時被$P" HIR "震得連退數步，吐血"
                                           "不止！\n" NOR);
                me->start_busy(2);
        } else
        {
                addn("neili", -100, me);
                msg += HIC "可是$p" HIC "強運內力，硬生生的擋住$P"
                       HIC "這一掌，沒有受到任何傷害。\n"NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
