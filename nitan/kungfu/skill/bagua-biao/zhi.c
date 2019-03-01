#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";

#define ZHI "「" HIY "乾坤一擲" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i, p;
        int n;
        int my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;

        if( userp(me) && !query("can_perform/bagua-biao/zhi", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHI "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
            query("skill_type", weapon) != "throwing" )
                return notify_fail("你現在手中並沒有拿著暗器。\n");

        if (weapon->query_amount() < 30)
                return notify_fail("至少要有三十枚暗器你才能施展" ZHI "。\n");

        if ((skill = me->query_skill("bagua-biao", 1)) < 120)
                return notify_fail("你的八卦鏢訣不夠嫻熟，難以施展" ZHI "。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功火候不夠，難以施展" ZHI "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你現在真氣不足，難以施展" ZHI "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg= HIY "只見$N" HIY "縱身一躍而起，一聲暴喝，十指箕張，將手中所有"
             "的" + weapon->name() + HIY "打了出去！\n";

        my_exp=query("combat_exp", me)+skill*skill/10*skill;
        ob_exp=query("combat_exp", target);

        if (random(my_exp/100) > ob_exp/100)
        {
                n = 5 + random(5);
                if (random(my_exp/100) >ob_exp/100) n += 5 + random(5);
                if (random(my_exp/200) >ob_exp/100) n += 5 + random(7);
                if (random(my_exp/400) >ob_exp/100) n += 5 + random(10);
                if (weapon->query_amount() < n) n = weapon->query_amount();

                msg += "$p" HIY "剎時只覺眼前金光萬道，反應不及，接連中了$P"
                       HIY+chinese_number(n)+query("base_unit", weapon)+
                       weapon->name() + HIY "！\n" NOR;
                target->receive_damage("qi", skill * 3 / 2 + random(skill * 3 / 2), me);
                target->receive_wound("qi", skill * 2 / 3 + random(skill * 2 / 3), me);
                p=query("qi", target)*100/query("max_qi", target);

                while (n--)
                {
                        COMBAT_D->clear_ahinfo();
                        weapon->hit_ob(me,target,query("jiali", me)+150+n*30);
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