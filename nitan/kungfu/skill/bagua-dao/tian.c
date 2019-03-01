#include <ansi.h>
#include <combat.h>

#define TIAN "「" HIY "天刀八勢" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int i, count;

        if( userp(me) && !query("can_perform/bagua-dao/tian", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(TIAN "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你所使用的武器不對，難以施展" TIAN "。\n");

        if ((int)me->query_skill("bagua-dao", 1) < 200)
                return notify_fail("你的八卦刀法不夠嫻熟，難以施展" TIAN "。\n");

        if ((int)me->query_skill("wai-bagua", 1) < 200)
                return notify_fail("你的外八卦神功不夠嫻熟，難以施展" TIAN "。\n");

        if ((int)me->query_skill("nei-bagua", 1) < 200)
                return notify_fail("你的內八卦神功不夠嫻熟，難以施展" TIAN "。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的內功修為不足，難以施展" TIAN "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在真氣不夠，難以施展" TIAN "。\n");

        if (me->query_skill_mapped("blade") != "bagua-dao")
                return notify_fail("你沒有激發八卦刀法，難以施展" TIAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        message_combatd(HIY "$N" HIY "驀地一振手中" + weapon->name() +
                        HIY "，發出萬千龍吟，霎時刀光滾滾，向四面湧出"
                        "，籠罩$n" HIY "全身。\n" NOR, me, target);

        count = me->query_skill("bagua-dao", 1) / 6;

        addn("neili", -250, me);
        addn_temp("apply/attack", count, me);

        for (i = 0; i < 8; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);

                addn_temp("pfm_tiandao", 1, me);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        delete_temp("pfm_tiandao", me);
        me->start_busy(1 + random(8));
        return 1;
}