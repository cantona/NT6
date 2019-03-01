// This program is a part of NITAN MudLIB
// qingxin.c 「清心劍」

#include <ansi.h>

inherit F_SSERVER;
string name() { return "清心劍"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int ainc, dinc;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「清心劍」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if ((int)me->query_skill("damo-jian", 1) < 200)
                return notify_fail("你的達摩劍法不夠嫻熟，不會使用「清心劍」。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在真氣不夠，無法使用「清心劍」。\n");

        if (me->query_skill_mapped("sword") != "damo-jian")
                return notify_fail("你沒有激發達摩劍法，無法使用「清心劍」。\n");

        if( query_temp("damo_qingxin", target) )
                return notify_fail("對方剛剛才中過達摩清心劍，你不必再用一次了。\n");

        msg = HIM "$N" HIM "將" + weapon->name() + "輕輕一抖，一股"
              "劍氣悄然而出，分作數路攻向$n" HIM "！\n" NOR;

        addn("neili", -200, me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if( !query_temp("powerup", target) )
        {
                msg += CYN "可是$p" CYN "看來似乎並沒有運用真氣提升" CYN
                       "戰力，$P" CYN "這一招沒有起到任何作用。\n" NOR;
                me->start_busy(2);
        } else
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "結果$p" HIR "覺得渾身一麻，手足軟"
                       "軟的竟然使不出一點力道！\n" NOR;
                ainc=query_temp("apply/attack", target);
                dinc=query_temp("apply/defense", target);
                addn_temp("apply/attack", -ainc, target);
                addn_temp("apply/defense", -dinc, target);
                set_temp("damo_qingxin", 1, target);
                me->start_call_out((: call_other, __FILE__, "remove_effect",
                                   target, ainc, dinc:), ap / 5);
        } else
        {
                msg += CYN "可是$p" CYN "內力深厚，使得$P" CYN
                       "這一招沒有起到任何作用。\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

void remove_effect(object me, int ainc, int dinc)
{
        if (! objectp(me))
                return;

        if( query_temp("damo_qingxin", me) )
        {
                delete_temp("damo_qingxin", me);
                addn_temp("apply/attack", ainc, me);
                addn_temp("apply/defense", dinc, me);
                tell_object(me, "你覺得力氣恢復了一些。\n");
        }
}