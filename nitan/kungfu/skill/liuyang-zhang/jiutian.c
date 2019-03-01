// This program is a part of NITAN MudLIB
// jiutian.c 九天式

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "九天式"; }

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
                return notify_fail("「九天式」只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("liuyang-zhang", 1) < 120)
                return notify_fail("你的六陽掌法不夠嫻熟，不會使用「九天式」。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的內功修為不夠高，難以運用「九天式」。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在真氣不夠，不能使用「九天式」。\n");

        msg = HIC "$N" HIC "雙掌一振，化出滿天掌影，團團籠罩住$n" HIC "！\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                damage+= query("jiali", me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 65,
                                           HIR "$p" HIR "無奈，只能硬擋一招，結果被$P"
                                           HIR "震得連退數步，吐血不止！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "可是$p" HIC "強運內力，硬生生的擋住$P"
                       HIC "這一掌，沒有受到任何傷害！\n"NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}