// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "修羅絕命指"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「修羅絕命指」只能在戰鬥中對對手使用。\n");

        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("你必須空手才能使用「修羅絕命指」！\n");

        if (me->query_skill("force") < 250)
                return notify_fail("你的內功的修為不夠，不能使用「修羅絕命指」！\n");

        if (me->query_skill("xiuluo-zhi", 1) < 150)
                return notify_fail("你的修羅指修為不夠，目前不能使用「修羅絕命指」！\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠，無法使用「修羅絕命指」！\n");

        if (me->query_skill_mapped("finger") != "xiuluo-zhi")
                return notify_fail("你沒有激發修羅指，不能使用「修羅絕命指」！\n");

        msg = HIB "$N忽然面露兇光，身形變的異常飄渺，在$n" HIB
                  "的四周遊走個不停，$n" HIB "正迷茫時，$N" HIB
                  "突然近身，毫無\n聲息的一指戳出！\n" NOR;

        ap = attack_power(me, "finger") + me->query_skill("force");
        dp = defense_power(target, "dodge") + target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "finger");
                addn("neili", -350, me);

                msg += HIR "只見$n" HIR "一聲慘叫，以被擊中要害部位，只覺得眼前一黑，似乎以看不清周圍的一切，身體搖搖欲墜！\n" NOR;
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 50);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -150, me);
                msg += CYN "可是$n" CYN "看破了$N" CYN "的企圖，輕輕"
                       CYN "向後飄出數丈，躲過了這一致命的一擊！\n"NOR;

                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
