#include <ansi.h>

inherit F_SSERVER;

#define LIAN "「" HIW "雄霸天下" NOR "」"
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int i;
        int count;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( userp(me) && !query("can_perform/badao/xiong", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(LIAN "只能對戰鬥中的對手使用。\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對！\n");

        if( query("neili", me)<3000 )
                return notify_fail("你的真氣不夠，無法施展" LIAN "！\n");

        if ((int)me->query_skill("force") < 900)
                return notify_fail("你的內功火候不夠，難以施展" LIAN "！\n");

        if ((int)me->query_skill("badao", 1) < 700)
                return notify_fail("你的霸刀還不到家，無法施展" LIAN "！\n");

        if (me->query_skill_mapped("blade") != "badao")
                return notify_fail("你沒有激發霸刀，無法施展" LIAN "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$N" HIY "使出失傳已久的霸刀絕技「" HIW "雄霸天下" HIY"」，刀法陡然加快，眨眼間，八刀劈出 ……\n" NOR;

        message_combatd(msg, me);
        addn("neili", -2600, me);

        count = me->query_skill("blade") / 3;
        addn_temp("apply/damage", count, me);

        for (i = 0; i < 8; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) && ! target->is_busy())
                        target->start_busy(1);
                        
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/damage", -count, me);
        me->start_busy(2 + random(3));
        return 1;
}