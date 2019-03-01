#include <ansi.h>
#include <combat.h>

#define CANG "「" HIW "天蠍藏針" NOR "」"

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int skill, i;

        if( userp(me) && !query("can_perform/jifeng-cixuefa/cang", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(CANG "只能對戰鬥中的對手使用。\n");

        weapon=query_temp("weapon", me);

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "dagger" )
                return notify_fail("你所使用的武器不對，難以施展" CANG "。\n");

        skill = me->query_skill("jifeng-cixuefa", 1);

        if (me->query_skill("force") < 120)
                return notify_fail("你的內功修為不夠，難以施展" CANG "。\n");

        if (me->query_skill("dodge") < 120)
                return notify_fail("你的輕功修為不夠，難以施展" CANG "。\n");

        if (skill < 100)
                return notify_fail("你的疾風刺穴法修為有限，難以施展" CANG "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不足，難以施展" CANG "。\n");

        if (me->query_skill_mapped("dagger") != "jifeng-cixuefa")
                return notify_fail("你沒有激發疾風刺穴法，難以施展" CANG "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "一聲叱喝，手中" + weapon->name() + HIY "連環五刺，招數"
              "層出不窮，閃電般朝$n" HIY "射去！\n" NOR;
        message_combatd(msg, me, target);
        addn("neili", -80, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(4));
        return 1;
}