#include <ansi.h>
#include <combat.h>

#define ZONG "「" HIY "萬佛朝宗" NOR "」"

inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count;
        int i;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( userp(me) && !query("can_perform/rulai-zhang/zong", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZONG "只能對戰鬥中的對手使用。\n");
 
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(ZONG "只能空手施展。\n");
                
        if( query("max_neili", me)<3000 )
                return notify_fail("你的內力修為不夠，難以施展" ZONG "。\n");

        if ((int)me->query_skill("force") < 280)
                return notify_fail("你的內功火候不足，難以施展" ZONG "。\n");

        if ((int)me->query_skill("rulai-zhang", 1) < 150)
                return notify_fail("你千手如來掌火候不夠，難以施展" ZONG "。\n");

        if (me->query_skill_prepared("strike") != "rulai-zhang")
                return notify_fail("你沒有準備千手如來掌，難以施展" ZONG "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不足，難以施展" ZONG "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "\n$N" HIY "當下更不耽擱，高呼佛號，輕飄飄拍出一掌，招式"
              "甚為尋常。但掌到中途，忽然微微搖晃，登時一掌變兩掌，兩掌變四"
              "掌，四掌變八掌！舖天蓋地拍向$n" HIY "。" NOR;

        ap=me->query_skill("strike")+query("str", me)*10;
        dp=target->query_skill("parry")+query("dex", target)*10;

        if (ap / 2 + random(ap) > dp)
        {
                // 增加點感官刺激:)
                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        me->start_busy(1);
                        addn("neili", -100, me);
                        msg += HIY "隨即又聽$N" HIY "高聲喝道：「" HIR "我佛如來" HIY
                               "」頃刻間，但見$N" HIY "八掌又變為十六掌，進而再幻化為"
                               "三十二掌，掌勢層層疊疊，波瀾壯闊，氣勢磅礡，盪氣回腸"
                               "。如海潮般向$n" HIY "湧去。\n\n" HIR "$n" HIR "面對這"
                               "無窮無盡的掌勢，竟然放棄了抵抗，面如死灰坐以待斃。\n" NOR;

                        message_sort(msg, me, target);
                        addn_temp("apply/attack", ap, me);
                        addn_temp("rulai-zhang/hit_msg", 1, me);
                        for (i = 0; i < 32; i++)
                        {
                                if (! me->is_fighting(target))
                                break;
                                if (random(5) < 2 && ! target->is_busy())
                                target->start_busy(1);

                                COMBAT_D->do_attack(me, target, 0, 0);
                        }
                        addn_temp("apply/attack", -ap, me);
                        delete_temp("rulai-zhang/hit_msg", me);
                        return 1;
                } else
                {
                        count = ap / 6;
                        msg += HIR "\n$n" HIR "見掌勢層層疊疊，有如海潮，一時"
                               "只覺頭暈目眩，難作抵擋。\n" NOR;
                }
        } else
        {
                msg += HIC "\n$n" HIC "見掌勢層層疊疊，有如海潮，連忙"
                       "振作精神，勉強抵擋。\n" NOR;
                count = 0;
        }

        message_sort(msg, me, target);
        addn_temp("apply/attack", count, me);
        addn_temp("rulai-zhang/hit_msg", 1, me);
        addn("neili", -300, me);

        for (i = 0; i < 8; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(1 + random(8));
        addn_temp("apply/attack", -count, me);
        delete_temp("rulai-zhang/hit_msg", me);
        return 1;
}