// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "天升劍訣" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, skill;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的內功的修為不夠，難以施展" + name() + "。\n");

        if (me->query_skill("liuyue-jian", 1) < 140)
                return notify_fail("你的流月劍舞修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "liuyue-jian")
                return notify_fail("你沒有激發流月劍舞，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "手腕一陣疾抖，劍身微顫，劍作龍吟。剎那間劍芒陡漲，"
              "如天河倒瀉一般灑向$n"
              HIW "。\n" NOR;

        message_combatd(msg, me, target);
        addn("neili", -100, me);
        skill = me->query_skill("liuyue-jian", 1);
        addn("apply/attack", skill, me);
        addn("apply/damage", skill/2, me);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        addn("apply/attack", -skill, me);
        addn("apply/damage", -skill/2, me);
        me->start_busy(1 + random(3));

        return 1;
}