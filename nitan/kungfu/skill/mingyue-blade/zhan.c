// This program is a part of NITAN MudLIB
// 天涯明月刀「斬.絕」

#include <ansi.h>
#include <combat.h>

string name() { return HIY "斬"HIR"."HIY"訣" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if (me->query_skill("force") < 180)
                return notify_fail("你的內功的修為不夠，難以施展" + name() + "。\n");

        if (me->query_skill("mingyue-blade", 1) < 120)
                return notify_fail("你的天涯明月刀修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<1200 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "mingyue-blade")
                return notify_fail("你沒有激發天涯明月刀，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");


        msg= HIC "$N" HIC "心中湧起沖天豪氣，就如馳騁沙場，殺將於千軍萬馬之間的壯烈情懷，一聲長嘯，離地而起，疾若閃電般往$n掠去。\n"
             HIC "同時，手中" + weapon->name() + HIC"由橫擺變成直指，強大和森寒徹骨的刀氣朝$n狂湧而去。\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                addn("neili", -240, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 210,
                                           HIR "$n" HIR "何曾見過如此高明的刀法，"
                                           "登時覺得眼前一片刀光，竟然不知如何躲避！\n" NOR);
                me->start_busy(2);
                if (ap / 3 + random(ap / 2) > dp && ! target->is_busy())
                        target->start_busy(3);
        } else
        {
                msg += CYN "$p" CYN "大吃一驚，也不招架，當即向後"
                       "橫移數尺，避開了$P" CYN "這一招。\n" NOR;
                addn("neili", -120, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}

