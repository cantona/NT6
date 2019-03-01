// This program is a part of NT MudLIB

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string name() { return "屠龍絕技"; }

int perform(object me, object target)
{
        string msg, pmsg;
        int damage, ap, dp;

        if (! target) target = offensive_target(me);

        if (! target
        ||      ! target->is_character()
        ||      ! me->is_fighting(target))
                return notify_fail("牽制攻擊只能對戰鬥中的對手使用。\n");

        if ((int)me->query_str() < 30)
                return notify_fail("你臂力不夠,不能使用這一絕技!\n");

        if ((int)me->query_skill("yinyun-ziqi", 1) < 100)
                return notify_fail("你氤氳紫氣的功力不夠不能使用倚天屠龍絕技!\n");

        if( query("neili", me)<800 )
                return notify_fail("你內力現在不夠, 不能使用倚天屠龍! \n");

        msg = HIY "$N長嘯一聲：" + YEL "武林至尊、寶刀屠龍。號令天下，莫敢不從。倚天不出，誰與爭鋒？\n" +
              HIY "手中兩般武器發出無窮罡氣，或如靈蛇盤騰，或如猛獸屹立，須臾間二十四字一齊寫畢。\n"NOR;

        ap=attack_power(me, "strike");

        dp=defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                addn("neili", -500, me);

                if (damage < 20)
                        pmsg = HIY"結果$n受到$N的內力反震，悶哼一聲。\n"NOR;
                else if (damage < 40)
                        pmsg = HIY"結果$n被$N以內力反震，「嘿」地一聲退了兩步。\n"NOR;
                else if (damage < 80)
                        pmsg = RED"結果$n被$N以內力一震，胸口有如受到一記重錘，連退了五六步！\n"NOR;
                else
                        pmsg = HIR"結果$n被$N的內力一震，眼前一黑，象一捆稻草一樣飛出去好幾丈遠！\n"NOR;
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 35, pmsg);

                me->start_busy(2);
                target->start_busy(random(3));

        }
        else
        {
                me->start_busy(2);
                addn("neili", -200, me);
                msg += CYN"可是$p看破了$P的企圖，並沒有上當，輕輕一閃便躲開了。\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}