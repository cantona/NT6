// This program is a part of NITAN MudLIB
// jianzhang.c  劍掌五連環

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIW "劍掌五連環" NOR; }

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

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對！\n");

        if( query("neili", me)<160 )
                return notify_fail("你的真氣不夠，無法施展" + name() + "！\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "！\n");

        if ((int)me->query_skill("huashan-sword", 1) < 50)
                return notify_fail("你的華山劍法還不到家，無法施展" + name() + "！\n");

        if (me->query_skill_mapped("sword") != "huashan-sword")
                return notify_fail("你沒有激發華山劍法，無法施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "使出華山派絕技「" HIW "劍掌五連環" HIY"」，身法陡然加快！\n" NOR;
        message_combatd(msg, me);
        addn("neili", -120, me);

        count = me->query_skill("sword");
        addn_temp("apply/attack", count, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (! target->is_busy() && random(3) == 1)
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(3));
        return 1;
}
