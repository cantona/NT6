#include <ansi.h>
#include <combat.h>

string name() { return HIG "嘯滄海" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;
        int fmsk;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("tanzhi-shentong", 1) < 200)
                return notify_fail("你的彈指神通不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("finger") != "tanzhi-shentong")
                return notify_fail("你沒有激發彈指神通，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("finger") != "tanzhi-shentong")
                return notify_fail("你沒有準備彈指神通，難以施展" + name() + "。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if( query("neili", me)<800 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIG "突然間$N" HIG "指鋒一轉，力聚指尖“嗤”的彈出一道紫芒，直襲$n"
              HIG "氣海大穴。\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "force");
        fmsk = me->query_skill("qimen-xuanshu", 1); 

        damage = damage_power(me, "finger");

        if (ap / 2 + random(ap) + fmsk > dp) 
        {
                target->receive_damage("jing", damage + fmsk / 2, me); 
                target->receive_wound("jing", damage / 2 + fmsk / 3, me); 
                addn("neili", -damage*3, target);

                if( query("neili", target)<0 )
                        set("neili", 0, target);

                msg += HIR "$n" HIR "只覺$N" HIR "指風襲體，隨即上體一"
                       "陣冰涼，頓感真氣渙散幾欲暈厥。\n" NOR;
                me->start_busy(2);
        } else
        {
                msg += CYN "可是$p" CYN "防守嚴密，緊守門戶，頓時令$P"
                       CYN "的攻勢化為烏有。\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
