//bafang.c  四象掌 八方乾坤

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「八方乾坤」只能在戰鬥中對對手使用。\n");

        if( query("max_neili", me)<600 )
                return notify_fail("你的內力還不夠高！\n");

        if( query("neili", me)<200 )
                return notify_fail("你沒內力了！\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功的修為不夠，不能使用八方乾坤!\n");

        if ((int)me->query_skill("sixiang-zhang", 1) < 120)
                return notify_fail("你的四象掌的修習不夠，無法使用八方乾坤！\n");

        if (me->query_skill_mapped("strike") != "sixiang-zhang")
                return notify_fail("你沒有激發四象掌，無法使用八方乾坤！\n");

        msg = HIY "$N" HIY "左手捏個掌訣，右手在胸前緩緩移動，竟封住了所有攻擊的方位\n"NOR;
        ap = me->query_skill("sixiang-zhang");
        dp = target->query_skill("dodge");
        if (random(me->query_skill("sixiang-zhang")) > target->query_skill("parry") / 3 || !living(target))
        {
                damage  = (int)me->query_skill("sixiang-zhang", 1);
                damage  = damage + (int)me->query_skill("strike", 1);
                damage  = damage + 200;

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "只見$N" HIR "腳踏陰陽八卦步，雙掌左右齊出，一正一反"
                                           HIR "左掌纏住$p的右\n掌，右掌卻從不可能的角度拍向$p胸口!!"
                                           HIR "$p頓時一陣厭惡！\n" NOR);
                addn("neili", -100, me);
                me->start_busy(2);
         } else
         {
                msg += CYN "可是$p" CYN "猛地向後一躍，跳出了$P"
                       CYN "的攻擊范圍。\n" NOR;
                me->start_busy(3);
         }
         message_combatd(msg, me, target);
         return 1;
}