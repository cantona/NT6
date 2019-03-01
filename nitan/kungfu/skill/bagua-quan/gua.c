#include <ansi.h>
#include <combat.h>

#define GUA "「" HIM "劈卦八卦拳" NOR "」"

inherit F_SSERVER;
int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if( userp(me) && !query("can_perform/bagua-quan/gua", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(GUA "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(GUA "只能空手施展。\n");

        if ((int)me->query_skill("bagua-quan", 1) < 70)
                return notify_fail("你的八卦拳法不夠嫻熟，難以施展" GUA "。\n");

        if (me->query_skill_mapped("cuff") != "bagua-quan") 
                return notify_fail("你沒有激發八卦拳法，難以施展" GUA "。\n");

        if (me->query_skill_prepared("cuff") != "bagua-quan") 
                return notify_fail("你沒有準備八卦拳法，難以施展" GUA "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在真氣不夠，難以施展" GUA "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIM "$N" HIM "突然身體一側，雙掌向下一沉，忽又向上一翻，朝著$n"
              HIM "的雙肩斜斜地劈去！\n" NOR;

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "cuff");
                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45,
                                           HIR "只因這招實在太過巧妙，$p" HIR "被"
                                           "$P" HIR "攻了個措手不及，大叫一聲，吐"
                                           "出一口鮮血！\n" NOR);
                me->start_busy(2);
        } else 
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN
                       "的這一招，鎮定解招，一絲不亂。"
                       "\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}