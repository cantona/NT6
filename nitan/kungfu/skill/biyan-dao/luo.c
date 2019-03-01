#include <ansi.h>
#include <combat.h>

#define LUO "「" HIW "瀑落九霄" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int i;

        if( userp(me) && !query("can_perform/biyan-dao/luo", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LUO "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你的武器不對，難以施展" LUO "。\n");

        if ((int)me->query_skill("biyan-dao", 1) < 80 )
                return notify_fail("你碧煙刀法不夠嫻熟，難以施展" LUO "。\n");

        if ((int)me->query_skill("force") < 120 )
                return notify_fail(RED"你內功火候不夠，難以施展" LUO "。\n");

        if (me->query_skill_mapped("blade") != "biyan-dao")
                return notify_fail("你沒有激發碧煙刀法，難以施展" LUO "。\n");

        if( query("neili", me)<80 )
                return notify_fail(HIC"你現在真氣不夠，難以施展" LUO "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "大喝一聲，手中" + weapon->name() + HIW
              "一振，便如飛瀑一般向$n" HIW "席卷而去！\n" NOR;
        message_combatd(msg, me, target);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn("neili", -80, me);
        me->start_busy(1 + random(3));
        return 1;
}