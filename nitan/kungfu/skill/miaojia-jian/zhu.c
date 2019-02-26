#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "黃龍吐珠" NOR; }

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

        if ((int)me->query_skill("miaojia-jian", 1) < 120)
                return notify_fail("你苗家劍法不夠嫻熟，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 150 )
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("你的內力修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "miaojia-jian")
                return notify_fail("你沒有激發苗家劍法，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$N" HIY "迴圈手中" + weapon->name() + HIY "施「黃龍吐珠」斜"
              "貫而出，劍尖頓時吐出一道黃芒，閃電般射向$n" + HIY "！\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");

                addn("neili", -150, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                           HIR "$n" HIR "見狀連忙格擋，可哪裏來得"
                                           "及，登時只覺全身一麻，劍氣已透胸而過。\n"
                                           NOR);
        } else
        {
                addn("neili", -50, me);
                me->start_busy(3);
                msg += CYN "可是" CYN "$n" CYN "一聲冷"
                       "笑，飛身一躍而起，避開了" CYN
                       "$N" CYN "發出的劍氣。\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}