#include <ansi.h>
#include <combat.h>

#define LUO "「" HIR "一劍落九雁" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int i, count;

        if( userp(me) && !query("can_perform/luoyan-jian/luo", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LUO "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不對，難以施展" LUO "。\n");

        if ((int)me->query_skill("luoyan-jian", 1) < 150)
                return notify_fail("你的回風落雁劍不夠嫻熟，難以施展" LUO "。\n");

        if (me->query_skill_mapped("sword") != "luoyan-jian")
                return notify_fail("你沒有激發回風落雁劍法，難以施展" LUO "。\n");

        if( query("neili", me)<400 )
                return notify_fail("你目前的真氣不夠，難以施展" LUO "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "\n$N" HIW "驀的一聲清嘯，施出衡山派絕學「" HIR "一劍落九雁"
              HIW "」，手中" + weapon->name() + HIW "青光盪漾。霎時間回風"
              "落雁劍劍招連綿湧出，有如神助，劍氣籠罩$n" HIW "四方。" NOR;

        message_sort(msg, me, target);

        ap = me->query_skill("sword");
        dp = target->query_skill("dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIY "$n" HIY "見$P" HIY "劍勢洶湧，寒意頓生，竟"
                      "被逼得連連後退，狼狽不已。\n" NOR;
                count = me->query_skill("luoyan-jian") / 40;
        } else
        {
                msg = HIC "$n" HIC "見$N" HIC "這幾劍來勢迅猛無比，毫"
                      "無破綻，只得小心應付。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        addn("neili", -200, me);
        addn_temp("apply/attack", count, me);

        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(9));
        return 1;
}