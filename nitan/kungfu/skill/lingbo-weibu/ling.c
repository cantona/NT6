// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "洛神凌波" NOR; }

inherit F_SSERVER;

void remove_effect(object me, int amount, int amount1);


int perform(object me, object target)
{
        string msg;
        int level, ap, dp, count;

        if (! target) target = offensive_target(me);
        if (! target || ! target->is_character() || ! me->is_fighting(target))
                return notify_fail("你一個人跳甚麼？\n");

        if ((level = me->query_skill("lingbo-weibu", 1)) < 120)
                return notify_fail("你的凌波微步還不夠熟練，難以施展" + name() + "。\n" NOR);

        if( query("neili", me)<600 )
                return notify_fail("你現在真氣不足，難以施展" + name() + "。\n" NOR);

        if( query_temp("lingbo", me) )
                return notify_fail("你已經運起「洛神凌波」了。\n");

        if( query("gender", me) == "女性" )
               msg = HIW "\n$N" HIW "提起真氣，依照先天伏羲六十"
                     "四卦，將凌波微步由頭到尾迅速無比的走了一次。 "
                     "$N" HIW "仿如洛神再生，身形頓時輕盈無比，"
                     "微步凌波，真個將逍遙二字發揮得淋漓盡至。\n" NOR;

        else   msg = HIC "\n$N" HIC "提起真氣，依照先天伏羲六十"
                     "四卦，將凌波微步由頭到尾迅速無比的走了一次。                    "
                     "只見$N" HIC "意態飄逸，影子亂飛，身形頓時輕"
                     "盈無比，真個將逍遙二字發揮得淋漓盡至。\n" NOR;

        message_combatd(msg, me, target);
/*
        count = level / 30;

        if (me->is_fighting())
                me->start_busy(2);

        addn_temp("dex", count, me);
        set_temp("lingbo", 1, me);
        me->start_call_out((: call_other,  __FILE__, "remove_effect", me, count :), level / 2);

        addn("neili", -400, me);
        return 1;
*/
        ap = attack_power(me, "dodge");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIW "$N猶如神仙下凡，$n跟隨着$N的舞步轉了個頭暈眼花\n" NOR;
                if (! target->is_busy())
                target->start_busy(ap / 60 + 4);
                addn("neili", -400, me);
                me->start_busy(1);
        } else
        {
                msg = HIG "可是$n看破了$N的舞步,儀態從容的躲了過去\n" NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;

}

/*
void remove_effect(object me, int amount, int amount1)
{
        if( query_temp("lingbo", me) )
        {
                addn_temp("dex", -amount, me);
                delete_temp("lingbo", me);
                tell_object(me, "你的「洛神凌波」運功完畢，將內力收回丹田。\n");
        }
}
*/