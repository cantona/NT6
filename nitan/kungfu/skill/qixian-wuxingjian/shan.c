#include <ansi.h>
#include <combat.h>

#define SHAN "「" HIY "七弦黃龍閃" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int skill;
        int ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( userp(me) && !query("can_perform/qixian-wuxingjian/shan", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! me->is_fighting(target))
                return notify_fail(SHAN "只能對戰鬥中的對手使用。\n");

        weapon=query_temp("weapon", me);

        if( weapon && query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" SHAN "。\n");

        skill = me->query_skill("qixian-wuxingjian", 1);

        if (skill < 160)
                return notify_fail("你的七弦無形劍修為有限，難以施展" SHAN "。\n");

        if (weapon && me->query_skill_mapped("sword") != "qixian-wuxingjian")
                return notify_fail("你沒有準備七弦無形劍，難以施展" SHAN "。\n");

        if (! weapon && me->query_skill_prepared("unarmed") != "qixian-wuxingjian")
                return notify_fail("你沒有準備七弦無形劍，難以施展" SHAN "。\n");

        if (me->query_skill("force") < 250)
                return notify_fail("你的內功修為不夠，難以施展" SHAN "。\n");

        if( query("neili", me)<600 )
                return notify_fail("你現在的真氣不夠，難以施展" SHAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        if (weapon)
        {
                msg = HIY "只見$N" HIY "一聲暴喝，單手迅速在" + weapon->name() +
                      HIY "上撥動數下，頓時琴音錚錚大響，只聽“啵”的\n一聲破空"
                      "之響，一束無形劍氣澎湃射出，直貫$n" HIY "而去。\n" NOR;
        } else
        {
                msg = HIY "只見$N" HIY "一聲暴喝，陡然間十指一並箕張，頓時琴音"
                      "錚錚大響，只聽“啵”的一聲破空之\n響，一束無形劍氣澎湃"
                      "射出，直貫$n" HIY "而去。\n" NOR;
        }

        ap = me->query_skill("force");
        dp = target->query_skill("force");

        if( query("max_neili", target)<10 )
        {
                msg += HIY "$N" HIY "這一招施出，可是$n"
                       HIY "竟像沒事一般，絲毫無損。\n" NOR;

                me->start_busy(2);
                addn("neili", -100, me);
        } else
        // 等級相差不大的玩家不受侵害
        if( userp(target) && query("max_neili", target)+500>query("max_neili", me) )
        {
                msg += HIY "可是$n" HIY "內力深厚，輕而易舉受下$N"
                       HIY "這一招，絲毫無損。\n" NOR;

                me->start_busy(2);
                addn("neili", -100, me);
        } else
        if (ap / 2 + random(ap) < dp)
        {
                msg += CYN "可是$n" CYN "急忙凝神聚氣，努力使自己"
                       "不受琴音的幹擾，終于化解了這一招。\n" NOR;

                me->start_busy(2);
                addn("neili", -100, me);
        } else
        {
                damage = skill * 3;
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 60,
                                           HIR "$n" HIR "只覺得$N" HIR "內力激盪，琴"
                                           "音猶如一柄利劍穿透鼓膜，“哇”的噴出一口"
                                           "鮮血。\n" NOR);

                me->start_busy(2);
                addn("neili", -300, me);
        }
        message_combatd(msg, me, target);

        return 1;
}