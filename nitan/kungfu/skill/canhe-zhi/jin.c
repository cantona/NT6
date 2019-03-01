// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "金剛劍氣" NOR; }

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用" + name() + "。\n");

        if ((int)me->query_skill("canhe-zhi", 1) < 160)
                return notify_fail("你的參合指修為有限，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("finger") != "canhe-zhi")
                return notify_fail("你現在沒有準備使用參合指，難以施展" + name() + "。\n");

        if( query("max_neili", me)<2500 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "雙手合十，微微一笑，頗得拈花之意。食指並中指"
              "輕輕一彈，頓時一屢罡氣電射而出，朝$n" HIY "襲去。\n" NOR;

        ap=attack_power(me, "finger") + me->query_skill("force", 1);
        dp=defense_power(target, "force") + target->query_skill("buddhism",1);
        me->start_busy(2);

        if ((int)target->query_skill("buddhism", 1) >= 200
            && random(5) == 1)
        {
                addn("neili", -400, me);
                me->start_busy(3);
                msg += HIY "但見$n" HIY "也即臉露笑容，衣袖輕輕一拂，順勢"
                       "裹上，頓將$N" HIY "的指力消逝殆盡。\n" NOR;
        } else
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "finger");
                addn("neili", -400, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45,
                                           (: final, me, target, damage :));
        } else
        {
                addn("neili", -200, me);
                me->start_busy(3);
                msg += CYN "$n" CYN "見$N" CYN "來勢洶湧，不敢輕易"
                       "招架，急忙提氣躍開。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        target->receive_damage("jing", damage / 6, me);
        target->receive_wound("jing", damage / 10, me);
        return  HIR "只聽“噗嗤”一聲，指力竟在$n" HIR
                "胸前穿了一個血肉模糊的大洞，透體而入。\n" NOR;
}