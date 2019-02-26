// liu.c

#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";

#define LIU "「" HIY "流星電閃" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i, p;
        int n;
        int my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/kunlun-qifa/liu", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(LIU "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
            query("skill_type", weapon) != "throwing" )
                return notify_fail("你現在手中並沒有拿着暗器，無法施展" LIU "。\n");

        if (weapon->query_amount() < 20)
                return notify_fail("至少要有二十枚暗器你才能施展" LIU "。\n");

        if ((skill = me->query_skill("kunlun-qifa", 1)) < 120)
                return notify_fail("你的崑崙器法尚不嫻熟，難以施展" LIU "。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功火候不夠，難以施展" LIU "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你內力不夠，難以施展" LIU "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg= HIY "$N" HIY "一聲冷笑，飛身躍起，半空中十指陡然箕張，手中的"
             + weapon->name() + HIY "便如流星一般向$n" HIY "飛去！\n";

        p=query("qi", target)*100/query("max_qi", target);
        my_exp=query("combat_exp", me)/100+skill*skill/1000*skill;
        ob_exp=query("combat_exp", target)/100;

        if (random(my_exp) > ob_exp)
        {
                n = 5 + random(5);
                if (random(my_exp) > ob_exp) n += 5 + random(5);
                if (random(my_exp / 2) > ob_exp) n += 5 + random(5);
                if (random(my_exp / 4) > ob_exp) n += 5 + random(10);
                if (weapon->query_amount() < n) n = weapon->query_amount();

                msg += "$p" HIY "只覺眼前寒光一閃而過，反應不及，接連中了$P"
                       HIY+chinese_number(n)+query("base_unit", weapon)+
                       weapon->name() + HIY "！\n" NOR;
                target->receive_wound("qi", skill / 3 + random(skill / 2), me);
                while (n--)
                {
                        COMBAT_D->clear_ahinfo();
                        weapon->hit_ob(me, target,
                                       query("jiali", me)+100+n*15);
                }
                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;
                        msg += "( $n" + eff_status_msg(p) + " )\n";
                message_combatd(msg, me, target);
        } else
        {
                msg += NOR + CYN "可是$p" CYN "眼明手快，躲過了$P" CYN "發出"
                       "的所有" + weapon->name() + CYN "。\n" NOR;
                message_combatd(msg, me, target);
        }

        weapon->set_amount(0);
        addn("neili", -100, me);
        me->start_busy(2);
        me->reset_action();
        return 1;
}