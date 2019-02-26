// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "金陽破嶺" NOR; }

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
            (string)query("skill_type", weapon) != "sword")
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("jiuyang-shengong", 1) < 220)
                return notify_fail("你的九陽神功不夠嫻熟，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force", 1) < 260)
                return notify_fail("你的內功根基不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("sword", 1) < 260)
                return notify_fail("你的基本劍法火候不夠，難以施展" + name() + "。\n");

        if ((int)query("max_neili", me) < 5500)
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if (query("neili", me) < 400)
                return notify_fail("你現在真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "jiuyang-shengong")
                return notify_fail("你沒有激發九陽神功為劍法，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "\n$N" HIY "一聲長吟，內力瀑漲，全身真氣貫與劍柄。手中" + weapon->name() + HIY
              "光芒四射，剎那間一股強勁的劍氣已湧向$n" HIY "！\n" NOR;

        addn("neili", -150, me);
        ap = attack_power(me, "sword") + me->query_skill("force", 1);
        dp = defense_power(target, "parry") + target->query_skill("force", 1);

        me->start_busy(2 + random(2));
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                damage+= query("jiali", me);
                addn("neili", -200, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 75 + random(50),
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
        return  HIY "$n" HIY "見此招快速無比，已無從躲閃，只得奮力招架，但是無奈$N" HIY
                "內力驚人，一股劍氣已經穿透$n" HIY "胸口，鮮血狂瀉而出。$n" HIY "頓覺"
                "內息散亂。\n" NOR;
}