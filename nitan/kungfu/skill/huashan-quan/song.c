
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "蒼鬆式" NOR; }

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

        if ((int)me->query_skill("huashan-quan", 1) < 40)
                return notify_fail("你的華山拳法不夠嫻熟，無法施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在真氣不夠，無法施展" + name() + "。\n");

        if (me->query_skill_prepared("cuff") != "huashan-quan")
                return notify_fail("你沒有準備使用劈石破玉拳，無法施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "怒喝一聲，右拳直出，剛猛有力，正是華山絕技「" HIG "蒼鬆式" HIY
               "」，拳風呼響，襲向$n" HIY "。\n"NOR;

        ap = attack_power(me, "cuff") + me->query_str()*10;
        dp = defense_power(target, "force") + target->query_str()*10;
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "cuff");

                addn("neili", -60, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "只見$P" HIR "一拳直出，$p" HIR
                                           "正欲擋格，卻已不及，一拳重重地打在身上！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "可是$p" HIC "奮力招架，硬生生的擋開了$P"
                       HIC "這一招。\n"NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}