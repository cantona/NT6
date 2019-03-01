#include <ansi.h>
#include <combat.h>

#define ZHEN "「" HIR "震雷乾坤" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, ap, dp, count;

        if( userp(me) && !query("can_perform/qujing-gunfa/zhen", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHEN "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "club" )
                return notify_fail("你使用的武器不對，難以施展" ZHEN "。\n");

        if (me->query_skill_mapped("club") != "qujing-gunfa")
                return notify_fail("你沒有激發取經棍法，難以施展" ZHEN "。\n");

        if(me->query_skill("qujing-gunfa", 1) < 200 )
                return notify_fail("你取經棍法不夠嫻熟，難以施展" ZHEN "。\n");

        if( (int)me->query_skill("force") < 350 )
                return notify_fail("你的內功修為不夠，難以施展" ZHEN "。\n");

        if( query("max_neili", me)<4500 )
                return notify_fail("你的內力修為太弱，難以施展" ZHEN "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣太弱，難以施展" ZHEN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "將手中" + weapon->name() + HIW "緩緩壓向$n"
              HIW "，棍體隱隱帶著風雷之勁，正是取經棍法殺著「" HIR "震"
              "雷乾坤" HIW "」！\n電光火石間，棍端竟全被紫電所籠罩，" +
              weapon->name() + HIW "幻作千百根相似，奔雷掣電般向$n" HIW
              "席卷而去。\n" NOR;

        ap = me->query_skill("club");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap * 2) > dp)
        {
                msg += HIR "$n" HIR "被$N" HIR "氣勢所撼，完全不知該如"
                       "何招架，竟而呆立當場！\n" NOR;
                count = ap / 8;
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIC "$n" HIC "見$N" HIC "氣勢如虹，心下凜然，急"
                       "忙凝神聚氣，小心應付！\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        addn("neili", -200, me);

        for (i = 0; i < 10; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(9));
        return 1;
}
