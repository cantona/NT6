#include <ansi.h>
#include <combat.h>

string name() { return HIW "擠字訣" NOR; }

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object target;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        skill = me->query_skill("taiji-quan", 1);

        if (skill < 150)
                return notify_fail("你的太極拳等級不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("cuff") != "taiji-quan")
                return notify_fail("你沒有激發太極拳，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("cuff") != "taiji-quan")
                return notify_fail("你現在沒有準備使用太極拳，無法使用" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "使出太極拳「擠」字訣，右腳實，左腳虛，粘連粘"
              "隨，右掌已搭住$n" HIW "左腕，橫勁發出。\n" NOR;

        damage = damage_power(me,"cuff");
        damage+= query("jiali", me);

        ap = attack_power(me,"cuff");
        dp = defense_power(target,"parry");
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -30, me);
                me->start_busy(2);
                target->receive_damage("jing", damage);
                target->receive_wound("jing", damage);
                msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK,
                       damage, 70, HIR "$n" HIR "稍不留神，讓$N" HIR
                       "這麼一擠，只覺全身力氣猶似流入汪洋大海，無影"
                       "無蹤。\n" NOR);
        }
        else
        {
                addn("neili", -10, me);
                msg += CYN "$n" CYN "見狀大吃一驚，急忙向後猛退數步，"
                       "終于避開了$N" CYN "這一擊。\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}