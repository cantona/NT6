#include <ansi.h>
#include <combat.h>

#define CHONG "「" HIY "衝刺攻擊" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i;

        if( userp(me) && !query("can_perform/qishi-ji/chong", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(CHONG "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "club" )
                return notify_fail("你所使用的武器不對，難以施展" CHONG "。\n");

        if (me->query_skill("qishi-ji", 1) < 100)
                return notify_fail("你聖騎士戟修為不夠，難以施展" CHONG "。\n");

        if (me->query_skill_mapped("club") != "qishi-ji")
                return notify_fail("你沒有激發聖騎士戟，難以施展" CHONG "。\n");

        if (me->query_skill("force") < 150)
                return notify_fail("你的內功修為不夠，難以施展" CHONG "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，難以施展" CHONG "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$N" HIY "狂哮一聲，手中" + weapon->name() + HIY "接連六"
              "刺，竟似幻作六道電光，盡數刺向$n" HIY "！\n" NOR;

        message_combatd(msg, me, target);
        addn("neili", -100, me);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(6));

        return 1;
}
