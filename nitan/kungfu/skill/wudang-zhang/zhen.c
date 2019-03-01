// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string name() { return "震字訣"; }

int perform(object me, object target)
{
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! target->is_character() ||
            ! me->is_fighting(target))
                return notify_fail("震字決只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("wudang-zhang", 1) < 100)
                return notify_fail("你的武當棉掌不夠嫻熟，不會使用震字訣。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的內力不夠！\n");

        msg = HIB "$N氣運丹田，使出棉掌震字決，雙掌泛起凌厲掌風，拍向$n。\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                addn("neili", -400, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                        HIR "$n 茫然不知所措，結果被$N一掌擊中前胸，$n眼前一黑，被擊飛出兩丈許！！！\n" NOR);
                me->start_busy(2);
        } else
        {
                addn("neili", 200, me);
                me->start_busy(2);
                msg += HIG "可是$p看破了$P的企圖，早就閃在了一邊。\n" NOR;
        }

        message_combatd(msg, me, target);
        return 1;
}

