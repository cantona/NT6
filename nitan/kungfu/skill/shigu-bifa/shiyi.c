#include <ansi.h>
#include <combat.h>

#define SHIYI "「" HIW "詩意縱橫" NOR "」"

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int skill, i;

        if( userp(me) && !query("can_perform/shigu-bifa/shiyi", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(SHIYI "只能對戰鬥中的對手使用。\n");

        weapon=query_temp("weapon", me);

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "dagger" )
                return notify_fail("你所使用的武器不對，難以施展" SHIYI "。\n");

        skill = me->query_skill("shigu-bifa", 1);

        if (me->query_skill("force") < 150)
                return notify_fail("你的內功修為不夠，難以施展" SHIYI "。\n");

        if (skill < 120)
                return notify_fail("你的石鼓打穴筆法修為有限，難以施展" SHIYI "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不足，難以施展" SHIYI "。\n");

        if (me->query_skill_mapped("dagger") != "shigu-bifa")
                return notify_fail("你沒有激發石鼓打穴筆法，難以施展" SHIYI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "縱步上前，手中" + weapon->name() + HIW "大開大"
              "合，招數連綿不絕，盪氣回腸，瞬間向$n" HIW "攻出數招！\n" NOR;
        message_combatd(msg, me, target);
        addn("neili", -80, me);

        for (i = 0; i < 4; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(4));
        return 1;
}