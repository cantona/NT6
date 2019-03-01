#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";

#define SHE "「" HIR "射日訣" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i;
        int n, p;
        mixed my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;

        if( userp(me) && !query("can_perform/fenglei-zifa/she", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHE "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
            query("skill_type", weapon) != "throwing" || 
            weapon->query_amount() < 1)
                return notify_fail("你現在手中並沒有拿著暗器，無法施展出" SHE "。\n");

        if ((skill = me->query_skill("fenglei-zifa", 1)) < 100)
                return notify_fail("你的風雷子法不夠嫻熟，無法施展" SHE "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你內力不足，無法施展" SHE "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        addn("neili", -80, me);
        weapon->add_amount(-1);

        msg = HIR "$N" HIR "身形微微一展，單手一晃，只聽“颼”的一聲，一" +
             query("base_unit", weapon)+weapon->name()+HIR"如閃電般"+
             "射向$n" HIR "而去。\n" NOR;

        me->start_busy(2);
        my_exp=query("combat_exp", me)+skill*skill/10*skill;
        my_exp /= 100;
        ob_exp=query("combat_exp", target)/100;
        p=query("qi", target)*100/query("max_qi", target);
        if (random(my_exp) > ob_exp * 2 / 3)
        {
                msg += HIR "$n" HIR "閃避不及，頓時被這招打了個血肉模糊"
                       "的窟窿，整個人疼得幾乎都要散架。\n" NOR;
                target->receive_wound("qi", skill / 2 + random(skill / 2), me);
                COMBAT_D->clear_ahinfo();
                weapon->hit_ob(me,target,query("jiali", me)+150);
                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;
                        msg += "( $n" + eff_status_msg(p) + " )\n";
                message_combatd(msg, me, target);
        } else
        {
                msg += CYN "可是$p" CYN "輕輕一縱，躲閃開了$P" CYN "發出的" +
                       weapon->name() + CYN "。\n" NOR;
                message_combatd(msg, me, target);
        }

        me->reset_action();
        return 1;
}