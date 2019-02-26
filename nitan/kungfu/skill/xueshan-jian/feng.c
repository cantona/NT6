// feng.c

#include <ansi.h>
#include <combat.h>

string name() { return HIW "劍氣封喉" NOR; }

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

        if (me->query_skill("force") < 240)
                return notify_fail("你的內功的修為不夠，難以施展" + name() + "。\n");

        if (me->query_skill("xueshan-jian", 1) < 160)
                return notify_fail("你的雪山劍法修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "xueshan-jian")
                return notify_fail("你沒有激發雪山劍法，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "只聽$N" HIW "一聲清嘯，手中" + weapon->name() +
              HIW "龍吟不止，迸出萬道光華，疾閃而過，無數勁風席捲"
              "$n" HIW "而去！\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        damage = damage_power(me, "sword");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90,
                                           HIR "$n" HIR "只感寒風襲體，全身一陣冰"
                                           "涼，已被$N" HIR "劍氣所傷。頓時喉嚨一"
                                           "甜，噴出一大口鮮血。\n" NOR);
        } else
        {
                addn("neili", -50, me);
                msg += CYN "可是$n" CYN "看破" CYN "$N" CYN
                       "的招數，飛身躍開丈許，終於將這陰寒劍"
                       "氣驅於無形。\n"NOR;
        }

        msg = HIW"$N隨即長嘯一聲，手中" + weapon->name() + HIW"疾卷，掀起萬朵雪花向前鋪天蓋地地撒去。\n"
              "在白茫茫的一片中，忽然出現萬朵梅花形劍花，穿透雪幕，朝四面八方狂射而出。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90,
                                           HIR "$n" HIR "只覺劍光束束，在自己身上絲絲劃過，一時全身劇痛，鮮血飛濺得到處都是。\n" NOR);
        } else
        {
                addn("neili", -50, me);
                msg += CYN "可是$p" CYN "絲毫不為$P"
                       CYN "華麗的劍光所動，穩穩將這一劍架開。\n" NOR;
        }
        me->start_busy(2 + random(2));
        message_combatd(msg, me, target);

        return 1;
}