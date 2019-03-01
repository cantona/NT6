// This program is a part of NITAN MudLIB
// foxin.c 佛心劍

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "佛心劍"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「佛心劍」只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的內功的修為不夠，不能使用這一絕技！\n");

        if (me->query_skill("fumo-jian", 1) < 135)
                return notify_fail("你的伏魔劍法修為不夠，目前不能使用佛心劍！\n");

        if( query("neili", me)<250 )
                return notify_fail("你的真氣不夠，不能使用佛心劍！\n");

        if (me->query_skill_mapped("sword") != "fumo-jian")
                return notify_fail("你沒有激發伏摩劍，不能使用佛心劍！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIC "$N" HIC "手中" + weapon->name() +
              HIC "緩緩伸出，封住了$n" + HIC "的退路，隨"
              "即一抖，化出數個劍花逼向$p" HIC "。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -150, me);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "結果$p" HIR "一個不慎，被$P" HIR
                                           "一劍劃過氣門，內息就如翻江倒海一"
                                           "般，身子搖搖欲墜！\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -60, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "並不慌亂，沉穩的將$P"
                       CYN "的招一一化解。\n"NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}
