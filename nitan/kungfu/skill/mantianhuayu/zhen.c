// This program is a part of NITAN MudLIB
// zheng.c

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "擲金針"; }

int perform(object me, object target)
{
        int skill, i;
        int n;
        int my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("你只能在戰鬥中對對手擲金針。\n");

        if( !objectp(weapon=query_temp("handing", me)) ||
            query("skill_type", weapon) != "throwing" )
                return notify_fail("你現在手中並沒有拿着暗器。\n");

        if (weapon->query_amount() < 20)
                return notify_fail("至少要有二十枚暗器你才能施展花雨金針。\n");

        if ((skill = me->query_skill("mantianhuayu", 1)) < 100)
                return notify_fail("你的滿天花雨擲金針不夠嫻熟，還不知怎麼擲出金針。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，無法擲出金針。\n");

        if( query("neili", me)<150 )
                return notify_fail("你內力不夠了。\n");

        if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        addn("neili", -100, me);
        weapon->add_amount(-10);

        msg= HIY "$N" HIY "飛身躍起，右手一張，頓時灑出一片金芒，"
             "手中" + weapon->name() + HIY "如急風暴雨一般直射$n"
             HIY "而去！\n" NOR;

        me->start_busy(2);
        my_exp=attack_power(me, "throwing");
        ob_exp=defense_power(target, "dodge");

        if (my_exp / 2 + random(my_exp) > ob_exp)
        {
                n = 1 + random(2);
                if (random(my_exp) > ob_exp) n += 1 + random(2);
                if (random(my_exp / 2) > ob_exp) n += 1 + random(2);
                if (random(my_exp / 4) > ob_exp) n += 1 + random(2);
                msg += HIR "結果$p" HIR "一聲慘嚎，連中了$P" HIR "發出的" HIR +
                       chinese_number(n)+query("base_unit", weapon)+
                       weapon->name() + HIR "。\n" NOR;
                target->receive_wound("qi", skill / 4 + random(skill / 4), me);
                while (n--)
                {
                        COMBAT_D->clear_ahinfo();
                        weapon->hit_ob(me, target,
                                       query("jiali", me)+100+n*10);
                }
                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;
                message_combatd(msg, me, target);
        } else
        {
                msg += HIG "可是$p" HIG "躲過了$P" HIG "漫天射出的" +
                       weapon->name() + HIG "。\n" NOR;
                message_combatd(msg, me, target);
        }

        me->reset_action();
        return 1;
}
