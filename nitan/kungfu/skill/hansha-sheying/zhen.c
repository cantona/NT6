#include <ansi.h>
#include <combat.h>

string name() { return HIR "無影針" NOR; }

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
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("handing", me)) ||
            query("skill_type", weapon) != "throwing" )
                return notify_fail("你現在手中並沒有拿着暗器，難以施展" + name() + "。\n");

        if (weapon->query_amount() < 10)
                return notify_fail("至少要有十枚暗器才能施展" + name() + "。\n");

        if ((skill = me->query_skill("hansha-sheying", 1)) < 120)
                return notify_fail("你的含沙射影不夠嫻熟，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        addn("neili", -100, me);
        weapon->add_amount(-10);

        msg= HIR "只聽“颼颼颼颼”數聲，一股勁風從$N" HIR "處激射而出，$N" HIR
             "手中" + weapon->name() + HIR "如煙雨般向$n" HIR "籠罩過去！\n";

        me->start_busy(2);
        my_exp=query("combat_exp", me)+skill*skill/10*skill;
        ob_exp=query("combat_exp", target);
        if (random(my_exp) > ob_exp)
        {
                n = 1 + random(2);
                if (random(my_exp) > ob_exp) n += 1 + random(2);
                if (random(my_exp / 2) > ob_exp) n += 1 + random(2);
                if (random(my_exp / 4) > ob_exp) n += 1 + random(2);

                msg += "結果$p" HIR "反應不及，中了$P" HIR +
                       chinese_number(n)+query("base_unit", weapon)+
                       weapon->name() + HIR "！\n" NOR;

                damage = damage_power(me, "throwing");
                target->receive_wound("qi", damage/2, me);
                p=query("qi", target)*100/query("max_qi", target);
                while (n--)
                {
                        COMBAT_D->clear_ahinfo();
                        weapon->hit_ob(me, target,
                                       query("jiali", me)+100+n*10);
                }
                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;
                        msg += "( $n" + eff_status_msg(p) + " )\n";
                message_combatd(msg, me, target);
        } else
        {
                msg += NOR + CYN "可是$p" CYN "躲過了$P" CYN "發出的所有" +
                       weapon->name() + NOR + CYN "。\n" NOR;
                message_combatd(msg, me, target);
        }
        me->reset_action();
        return 1;
}