// This program is a part of NITAN MudLIB
// hua.c 化骨綿掌

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "化骨"; }

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int damage;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("辣手化骨只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，無法施展化骨掌。\n");

        if ((int)me->query_skill("huagu-mianzhang", 1) < 100)
                return notify_fail("你的化骨綿掌還不夠嫻熟，不會化骨掌。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠，不能化骨。\n");

        if (me->query_skill_mapped("strike") != "huagu-mianzhang")
                return notify_fail("你沒有激發化骨綿掌，無法施展化骨掌。\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        addn("neili", -100, me);

        msg = MAG "$N" MAG "掌出如風，輕輕拍向$n" MAG "的肩頭。\n"NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "strike");
                damage+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                          (: final, me, target, damage :));
        } else
        {
                msg += CYN "可是$p" CYN "急忙閃在一旁，躲了開去。\n" NOR;
                me->start_busy(3);
        }

        message_combatd(msg, me, target);
        return 1;
}

string final(object me, object target, int damage)
{
        int lvl = me->query_skill("huagu-mianzhang", 1) / 2 * 3;

        target->affect_by("huagu",
                (["level":query("jiali", me)+random(query("jiali", me)),
                   "id":query("id", me),
                   "duration" : lvl / 60 + random(lvl / 60) ]));

        return HIR "結果只聽撲的一聲，$p被$P一掌拍中，只"
               "覺得全身暖洋洋的，感到有點輕飄無力。\n" NOR;
}
