// This program is a part of NITAN MudLIB
// qian.c

#include <ansi.h>
#include <combat.h>

string name() { return HIR "乾坤無量" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if (me->query_skill("force") < 150)
                return notify_fail("你的內功的修為不夠，難以施展" + name() + "。\n");

        if (me->query_skill("wuliang-jian", 1) < 100)
                return notify_fail("你的無量劍法修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIR "只見$N" HIR "手中" + weapon->name() + HIR "“唰"
              "唰唰唰”連攻四劍，劍招去勢極快，全然籠罩$n" HIR "！\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -150, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "結果$n" HIR "阻擋不及，頓時被$N"
                                           HIR "斬中數劍，傷口見骨，苦不堪言。\n"
                                           NOR);
        } else
        {
                addn("neili", -50, me);
                me->start_busy(3);
                msg += CYN "可卻見" CYN "$n" CYN "猛的拔地而起，避開了"
                       CYN "$N" CYN "的劍招。\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
