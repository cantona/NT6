#include <ansi.h>
#include <combat.h>

#define XING "「" HIW "星羅棋佈" NOR "」"

inherit F_SSERVER;
 
int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, damage;

        if( userp(me) && !query("can_perform/sixiang-zhang/xing", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(XING "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(XING "只能空手施展。\n");

        skill = me->query_skill("sixiang-zhang", 1);

        if (skill < 60)
                return notify_fail("你的四象掌法等級不夠，難以施展" XING "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，難以施展" XING "。\n");
 
        if (me->query_skill_mapped("strike") != "sixiang-zhang")
                return notify_fail("你沒有激發四象掌法，難以施展" XING "。\n");

        if (me->query_skill_prepared("strike") != "sixiang-zhang")
                return notify_fail("你現在沒有準備使用四象掌法，無法使用" XING "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "一聲清嘯，雙掌紛飛貫出，掌影重重疊疊，虛實難"
              "辨，全全籠罩$n" HIW "全身。\n" NOR;

        ap = me->query_skill("strike");
        dp = target->query_skill("parry");
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -80, me);
                damage = ap / 3 + random(ap / 3);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 10,
                                           HIR "$n" HIR "一時無法勘破這玄奇的掌法"
                                           "，接連中了數招，身陷其中，無法自拔。\n"
                                           NOR);
                me->start_busy(2);
                if (ap / 2 + random(ap) > dp && ! target->is_busy())
                        target->start_busy(ap / 60 + 1);
        } else
        {
                msg += CYN "可是$p" CYN "的看破了$P" CYN
                       "的掌法，巧妙的拆招，沒露半點破綻"
                       "。\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}