#include <ansi.h>
#include <combat.h>

#define QIAN "「" HIW "千掌環" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int attack_time, i;

        if( userp(me) && !query("can_perform/yinyang-zhang/qian", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(QIAN "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(QIAN "只能空手施展。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((int)me->query_skill("yinyang-zhang", 1) < 100)
                return notify_fail("你陰陽掌不夠嫻熟，難以施展" QIAN "。\n");

        if (me->query_skill_prepared("strike") != "yinyang-zhang")
                return notify_fail("你沒有準備陰陽掌，難以施展" QIAN "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，難以施展" QIAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        ap = me->query_skill("strike");
        dp = target->query_skill("dodge");

        msg = HIC "\n$N" HIC "一聲長嘯，將內力運于雙掌之上，施出絕招"
              "「" HIW "千掌環" HIC "」，剎時間塵土漫天飛揚，$N" HIC 
              "雙掌不斷地連續拍出，攻勢凌厲，令人不敢大意。\n" NOR;
        message_sort(msg, me, target);
        
        if (random(ap) > dp / 2)
        {
                msg = HIR "結果$n" HIR "目不暇接，頓時被$N" HIR "掌"
                      "風所困，頓時陣腳大亂。\n" NOR;
                addn_temp("apply/attack", 60, me);
        } else
        {
                msg = HIY "$n" HIY "看清$N" HIY "這幾招的來路，但"
                      "內勁所至，掌風犀利，也只得小心抵擋。\n" NOR;          
        }
        message_vision(msg, me, target);

        attack_time += 3 + random(ap / 40);

        if (attack_time > 6)
                attack_time = 6;

        addn("neili", -attack_time*20, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        addn_temp("apply/attack", -50, me);
        me->start_busy(1 + random(attack_time));

        return 1;
}