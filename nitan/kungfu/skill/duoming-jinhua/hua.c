#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIM "天外飛花" NOR; }

#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
        int skill, i;
        int n, p;
        int my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
            (string)query("skill_type", weapon) != "throwing")
                return notify_fail("你現在手中並沒有拿着暗器。\n");

        if (weapon->query_amount() < 10)
                return notify_fail("至少要有十枚暗器你才能施展" + name() + "。\n");

        if ((skill = me->query_skill("duoming-jinhua", 1)) < 120)
                return notify_fail("你的奪命金花不夠嫻熟，不會施展" + name() + "。\n");

        if (me->query_skill_mapped("throwing") != "duoming-jinhua")
                return notify_fail("你沒有激發奪命金花基本暗器，無法施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，不能施展" + name() + "。\n");

        if ((int)query("neili", me) < 150)
                return notify_fail("你內力不夠了。\n");

        addn("neili", -100, me);
        weapon->add_amount(-10);

        msg= HIC "只聽“颼颼颼颼”數聲，$N" HIC "隨手一擺，"
             "手中" + weapon->name() + HIC "如花瓣飛舞般向$n" HIC "籠罩過去！\n" NOR;

        me->start_busy(2);
        my_exp = attack_power(me, "throwing");
        ob_exp = defense_power(target, "dodge");

        if (my_exp / 2 + random(my_exp) > ob_exp)
        {
                n = 1 + random(2);
                if (random(my_exp) > ob_exp) n += 1 + random(2);
                if (random(my_exp / 2) > ob_exp) n += 1 + random(2);
                if (random(my_exp / 4) > ob_exp) n += 1 + random(2);
                msg += HIR "結果$p" HIR "反應不及，中了$P" HIR +
                       chinese_number(n) + query("base_unit", weapon) +
                       weapon->name() + HIR "！\n" NOR;

                target->receive_wound("qi", damage_power(me, "throwing")/4, me);

                p=query("qi", target)*100/query("max_qi", target);

                while (n--)
                {
                        COMBAT_D->clear_ahinfo();
                        weapon->hit_ob(me, target,
                                       query("jiali", me) + 100 + n * 10);
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
