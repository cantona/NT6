#include <ansi.h>
#include <combat.h>

#define LUO "「" HIR "星羅棋布" NOR "」"

inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
        int skill, i, p;
        int n;
        int my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/heixue-shenzhen/luo", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(LUO "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
            query("skill_type", weapon) != "throwing" )
                return notify_fail("你現在手中並沒有拿著暗器。\n");

        if (weapon->query_amount() < 20)
                return notify_fail("至少要有二十枚暗器才能施展" LUO "。\n");

        if ((skill = me->query_skill("heixue-shenzhen", 1)) < 140)
                return notify_fail("你的黑血神針不夠嫻熟，難以施展" LUO "。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功火候不夠，難以施展" LUO "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你現在真氣不足，難以施展" LUO "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg= HIR "$N" HIR "縱身躍起，陡然間十指猛張，竟將手中所有的"
             + weapon->name() + HIR "打出，籠罩$n" HIR "四方！\n" NOR;

        my_exp=query("combat_exp", me)+skill*skill/10*skill;
        ob_exp=query("combat_exp", target);

        if (random(my_exp) > ob_exp)
        {
                n = 4 + random(4);
                if (random(my_exp) > ob_exp) n += 4 + random(4);
                if (random(my_exp / 2) > ob_exp) n += 4 + random(4);
                if (random(my_exp / 4) > ob_exp) n += 4 + random(8);
                if (weapon->query_amount() < n) n = weapon->query_amount();

                msg += HIR "結果$n" HIR "躲閃不及，全身上下被$P" HIR "射出"
                       HIR + chinese_number(n) + HIR "個血肉淋漓的窟窿，慘"
                       "不忍睹。\n" NOR;
                target->receive_damage("qi", skill + random(skill), me);
                target->receive_wound("qi", skill / 2 + random(skill / 2), me);
                p=query("qi", target)*100/query("max_qi", target);
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
                msg += CYN "$p" CYN "見得$P" CYN "招數奇特，不敢大意，當"
                       "即飛身躲開了所有暗器。\n" NOR;
                message_combatd(msg, me, target);
        }

        weapon->set_amount(0);
        addn("neili", -100, me);
        me->start_busy(2);
        me->reset_action();
        return 1;
}