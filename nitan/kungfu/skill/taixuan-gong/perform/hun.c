// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;

#define HUN "「" HIW "混天一氣" NOR "」"

string final(object me, object target, int damage);

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;

        if( userp(me) && !query("can_perform/taixuan-gong/hun", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target)target = me->select_opponent();

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUN "只能對戰鬥中的對手使用。\n");
 
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(HUN "只能空手施展。\n");

        if (me->query_skill("taixuan-gong", 1) < 120)
                return notify_fail("你的太玄功還不夠嫻熟，難以施展" HUN "。\n");

        if (me->query_skill_mapped("unarmed") != "taixuan-gong")
                return notify_fail("你現在沒有激發太玄功為拳腳，難以施展" HUN "。\n");

        if (me->query_skill_mapped("force") != "taixuan-gong")
                return notify_fail("你現在沒有激發太玄功為內功，難以施展" HUN "。\n");

        if (me->query_skill_prepared("unarmed") != "taixuan-gong")
                return notify_fail("你現在沒有準備使用太玄功，難以施展" HUN "。\n");

        if( query("neili", me)<600 )
                return notify_fail("你的內力不夠，難以施展" HUN "。\n");
 
        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIG "\n$N" HIG "雙手合十，雙目微閉，太玄奧義自心底湧出，猛然間，$N"
              HIG "雙手向前推出，一股強勁的氣流襲向$n " HIG "。\n" NOR;
 
        ap=attack_power(me,"unarmed")+query("con", me)*10;

        dp=defense_power(target,"force")+query("con", target)*10;

        addn("neili", -150, me);

        if (ap / 2 + random(ap) < dp)
        {
                msg += HIY "然而$n" HIY "全力抵擋，終於將$N" HIY
                       "發出的氣流擋住。\n" NOR;
                me->start_busy(2);
        } else
        {
                addn("neili", -100, me);
                me->start_busy(2);
                damage = defense_power(me, "unarmed");
                // target->addn("neili", -(me->query_skill("taixuan-gong", 1) + 
                            // random(me->query_skill("taixuan-gong", 1))), me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(10),
                                           (: final, me, target, damage :));

        }
        message_combatd(sort_msg(msg), me, target);
        return 1;
}


string final(object me, object target, int damage)
{
        target->receive_damage("jing", damage / 2, me);
        target->receive_wound("jing", damage / 3, me);
        target->busy(1);
        return  HIR "$n" HIR "急忙飛身後退，可是氣流射"
                "得更快，只聽$p" HIR "一聲慘叫，一股氣"
                "流已經透體而過，鮮血飛濺！$n" HIR "頓"
                "覺精力渙散，無法集中。\n" NOR;
}
