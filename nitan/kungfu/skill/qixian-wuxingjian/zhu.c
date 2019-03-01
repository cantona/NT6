#include <ansi.h>
#include <combat.h>

#define ZHU "「" HIW "七弦連環誅" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int i;
        int skill;
        int ap, an, dn;
        int count;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( userp(me) && !query("can_perform/qixian-wuxingjian/zhu", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! me->is_fighting(target))
                return notify_fail(ZHU "只能對戰鬥中的對手使用。\n");

        skill = me->query_skill("qixian-wuxingjian", 1);

        if (me->query_skill("force") < 300)
                return notify_fail("你的內功的修為不夠，現在無法使用" ZHU "。\n");

        if (skill < 180)
                return notify_fail("你的七弦無形劍修為有限，現在無法使用" ZHU "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠，無法運用" ZHU "。\n");

        weapon=query_temp("weapon", me);

        if( weapon && query("skill_type", weapon) != "sword" )
                return notify_fail("你不能使用這種兵器施展" ZHU "。\n");

        if (weapon && me->query_skill_mapped("sword") != "qixian-wuxingjian")
                return notify_fail("你現在沒有準備使用七弦無形劍，無法施展" ZHU "。\n");

        if (! weapon && me->query_skill_prepared("unarmed") != "qixian-wuxingjian")
                return notify_fail("你現在沒有準備使用七弦無形劍，無法施展" ZHU "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        if (weapon)
        {
                msg = HIW "只見$N" HIW "雙目微閉，單手在" + weapon->name() +
                      HIW "上輕輕撥動，頓時只聽“啵啵啵”破空之聲連續不斷"
                      "，數股破\n體無形劍氣激射而出，直奔$n" HIW "而去。\n" NOR;
        } else
        {
                msg = HIW "只見$N" HIW "雙目微閉，雙手輕輕舞弄，陡然間十指一"
                      "並箕張，頓時只聽“啵啵啵”破空之聲連續不\n斷，數股破"
                      "體無形劍氣激射而出，直奔$n" HIW "而去。\n" NOR;
        }

        ap = me->query_skill("force");
        an=query("max_neili", me);
        dn=query("max_neili", target);

        if (an > dn)
        {
                msg += HIR "$p" HIR "只感到$P" HIR "內力澎湃，洶湧而至，霎"
                       "時心神懼碎，呆立當場！\n" NOR;
                count = ap / 8;
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIC "$n" HIC "只感到$P" HIC "內力澎湃，洶湧而至，急"
                       "忙凝神聚氣，小心應付。\n" NOR;
                count = ap / 15;
                addn_temp("apply/attack", count, me);
        }

        message_combatd(msg, me, target);
        addn("neili", -250, me);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(3) == 0 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(6));
        addn_temp("apply/attack", -count, me);

        return 1;
}