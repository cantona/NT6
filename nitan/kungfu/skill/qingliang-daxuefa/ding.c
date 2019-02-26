#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIC "透骨釘" NOR; }

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        weapon=query_temp("weapon", me);

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "dagger" )
                return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");

        skill = me->query_skill("qingliang-daxuefa", 1);

        if (me->query_skill("force") < 150)
                return notify_fail("你的內功修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (skill < 100)
                return notify_fail("你清涼打穴法修為有限，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("dagger") != "qingliang-daxuefa")
                return notify_fail("你沒有激發清涼打穴法，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIC "$N" HIC "側身將手中" + weapon->name() + HIC "斜刺而出，一式「"
              HIR "透骨釘" NOR + HIC "」卷帶着呼呼風聲，將$n" HIC "包圍緊裹。\n" NOR;

        ap = attack_power(me, "dagger");
        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -200, me);
                damage = damage_power(me, "dagger");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "頓時只聽得“噗嗤”一聲，$n" HIR
                                           "胸口被$N" HIR "這一招刺中，濺出一柱鮮血。\n" NOR);
                me->start_busy(1);
                if (ap / 3 + random(ap) > dp && ! target->is_busy())
                        target->start_busy(ap / 80 + 1);
        } else
        {
                msg += CYN "可是$p" CYN "的看破了$P" CYN
                       "的招式，巧妙的一一拆解，沒露半點"
                       "破綻！\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}