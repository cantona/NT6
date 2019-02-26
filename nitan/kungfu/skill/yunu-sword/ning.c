// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIM "寧氏一劍" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if (me->query_skill("dodge", 1) < 100)
                return notify_fail("你的基本輕功的修為不夠，難以施展" + name() + "。\n");

        if (me->query_skill("force", 1) < 100)
                return notify_fail("你的基本內功的修為不夠，難以施展" + name() + "。\n");

        if (me->query_skill("yunv-sword", 1) < 100)
                return notify_fail("你的淑女劍法修為不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "yunv-sword")
                return notify_fail("你沒有激發淑女劍法，難以施展" + name() + "。\n");

        if( query("neili", me)<250 )
                return notify_fail("你現在真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "\n$N" HIW "嬌喝一聲，飛身而起，使出絕招「" HIM "寧氏一劍" HIW "」將畢生功力運於\n"
              + weapon->name() + HIW "上，頓時劍光四射，劍勢如虹，將$n" HIW "籠罩" HIW "。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -220, me);
                me->start_busy(1 + random(3));
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIR "$n" HIR "開料不及，正欲躲閃，卻已經中劍。\n" NOR);
        } else
        {
                addn("neili", -120, me);
                me->start_busy(2);
                msg += CYN "可是$n" CYN "隨手招架，竟將這招化解。\n"NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}