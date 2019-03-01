#include <ansi.h>
#include <combat.h>

#define GUI "「" HIR "鬼魅身法" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int ap, dp;
        int skill;

        if( userp(me) && !query("can_perform/pixie-jian/gui", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(GUI "只能對戰鬥中的對手使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        skill = me->query_skill("pixie-jian", 1);

        if (skill < 100)
                return notify_fail("你的辟邪劍法不夠嫻熟，難以施展" GUI "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在的真氣不足，難以施展" GUI "。\n");

        if (me->query_skill_mapped("dodge") != "pixie-jian")
                return notify_fail("你沒有準備使用辟邪劍法，難以施展" GUI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIR "$N" HIR "身子忽進忽退，宛若鬼魅，身形詭秘異常，在$n"
              HIR "身邊飄忽不定。\n" NOR;

        ap=me->query_skill("sword")*3/2+query("level", me)*20+
             me->query_skill("martial-cognize", 1);

        dp=target->query_skill("parry")+query("level", target)*20+
             target->query_skill("martial-cognize", 1);

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$p" HIR "霎時只覺眼花繚亂，只能緊守門戶，不"
                       "敢妄自出擊！\n" NOR;
                target->start_busy(ap / 45 + 2);
                me->start_busy(1);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的身法，並沒有受"
                       "到任何影響。\n" NOR;
                me->start_busy(2);
        }
        addn("neili", -50, me);
        message_combatd(msg, me, target);

        return 1;
}
