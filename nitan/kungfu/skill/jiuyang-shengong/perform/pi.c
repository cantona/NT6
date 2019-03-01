// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "驕陽劈天" NOR; }

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (userp(me) && !query("can_learn/jiuyang-shengong/enable_weapon", me))
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if (! objectp(weapon = query_temp("weapon", me)) ||
            (string)query("skill_type", weapon) != "blade")
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("jiuyang-shengong", 1) < 220)
                return notify_fail("你的九陽神功不夠嫻熟，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force", 1) < 260)
                return notify_fail("你的內功根基不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("blade", 1) < 260)
                return notify_fail("你的基本刀法火候不夠，難以施展" + name() + "。\n");

        if ((int)query("max_neili", me) < 5500)
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if (query("neili", me) < 400)
                return notify_fail("你現在真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "jiuyang-shengong")
                return notify_fail("你沒有激發九陽神功為刀法，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "\n$N" HIW "猛然間飛身而起，半空中一聲長嘯，內力源源不絕地湧"
              "入" + weapon->name() + HIW "，剎那間刀芒奪目，自天而下，劈向$n" HIW "！\n" NOR;

        addn("neili", -150, me);
        ap = attack_power(me, "blade") + me->query_skill("force", 1);
        dp = defense_power(target, "parry") + target->query_skill("force", 1);

        me->start_busy(2 + random(2));
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                damage+= query("jiali", me);
                addn("neili", -200, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 85 + random(50),
                                           (: final, me, target, damage :));
        } else
        {
                msg += HIC "可是$n" HIC "看透$P" HIC "此招之中的破綻，鎮"
                       "定逾恆，全神應對自如。\n" NOR;
        }
        message_sort(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        addn("neili", -(damage/4), target);
        addn("neili", -(damage/8), target);
        return  HIR "$n" HIR "只覺刀芒奪目，正猶豫間到刀芒已穿透$n" HIR "身體，頓時"
                "鮮血狂湧，內息散亂。\n" NOR;
}
