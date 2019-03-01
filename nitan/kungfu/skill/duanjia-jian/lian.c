#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "五絕連環" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg, skill;
        int i;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || (query("skill_type", weapon) != "staff"
            && query("skill_type", weapon) != "sword") )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("duanjia-jian", 1) < 120)
                return notify_fail("你的段家劍法不夠嫻熟，難以施展" + name() + "。\n");

        skill=query("skill_type", weapon);

        if (me->query_skill_mapped(skill) != "duanjia-jian")
                return notify_fail("你現在沒有激發段家劍，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "深吸一口氣，腳下步步進擊，穩重之極，手中的" +
              weapon->name() + HIY "使得猶如飛龍一般，纏繞向$n" HIY "！\n" NOR;
        message_combatd(msg, me, target);

        addn("neili", -100, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(5) == 0 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(3));
        return 1;
}
