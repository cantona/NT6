// This program is a part of NITAN MudLIB
// xue.c 冰雪紛飛

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIW "冰雪紛飛" NOR; }

string *desc = ({
HIW"\n                  ^長空雷隱！^          \n" NOR,
HIY  "                ^^^山風凜冽！^^^       \n" NOR,
RED  "             ^^^^^^回光幻電！^^^^^^  \n" NOR,
HIM  "          ^^^^^^^^^冰河開凍！^^^^^^^^^ \n" NOR,
HIC  "       ^^^^^^^^^^^^天山雪崩！^^^^^^^^^^^^ \n" NOR,
});

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, level;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不對！\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真氣不夠！\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的基本內功火候不夠！\n");

        if ((int)me->query_skill("tianshan-zhang", 1) < 100)
                return notify_fail("你的天山杖法還不到家，無法使用" + name() + "！\n");

        if (me->query_skill_mapped("staff") != "tianshan-zhang")
                return notify_fail("你沒有激發天山杖法，使不了" + name() + "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "使出星宿絕技「冰雪紛飛」，招式變得詭秘異常！\n" NOR;
        message_combatd(msg, me);
        addn("neili", -120, me);
        level = me->query_skill("tianshan-zhang", 1);
        addn("apply/attack", level/2, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                msg = desc[i];
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn("apply/attack", -level/2, me);
        me->start_busy(1 + random(3));
        return 1;
}
