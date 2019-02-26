#include <ansi.h>
#include <combat.h>

#define HAN "「" HIW "極天寒掌" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if( userp(me) && !query("can_perform/hanbing-zhang/han", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HAN "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(HAN "只能空手施展。\n");

        if ((int)me->query_skill("hanbing-zhang", 1) < 160)
                return notify_fail("你寒冰掌不夠嫻熟，難以施展" HAN "。\n");

        if (me->query_skill_prepared("strike") != "hanbing-zhang")
                return notify_fail("你沒有準備寒冰掌，難以施展" HAN "。\n");

        if (me->query_skill("force") < 180)
                return notify_fail("你的內功修為不夠，難以施展" HAN "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不夠，難以施展" HAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        ap = me->query_skill("strike");
        dp = target->query_skill("parry");

        msg = HIY "\n$N" HIY "運轉真氣，將內力注於掌上，施出"
              "絕招「" HIW "極天寒掌" HIY "」，雙掌猛然拍向$n" 
              HIY "，掌風陰寒無比，透出陣陣寒氣，猶如置身冰天"
              "雪地中一般，令人不寒而慄。\n" NOR;

        if (ap / 2 + random(ap) > dp)
        {
                damage = (int)me->query_skill("hanbing-zhang", 1) * 2;
                damage += random(damage);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                           HIR "但見$N" HIR "雙掌拍來，掌風作響，"
                                           "寒氣逼人。$n" HIR "頓覺心驚膽戰，"
                                           "毫無招架之力，微遲疑間$N" HIR "這掌"
                                           "已正中$n" HIR "胸口，頓將$p震退數步。"
                                           " \n" NOR);

                me->start_busy(3);
                addn("neili", -220, me);
        } else
        {
                msg += CYN "$n" CYN "見$N" CYN "這掌拍來，內力"
                       "充盈，氣勢凌人，只得奮力向後一縱，才躲"
                       "過這一掌。\n" NOR;

                me->start_busy(4);
                addn("neili", -120, me);
        }
        message_sort(msg, me, target);
        return 1;
}