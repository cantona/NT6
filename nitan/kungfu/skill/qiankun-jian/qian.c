// qian.c

#include <ansi.h>
#include <combat.h>

#define QIAN "「" HIY "乾坤勁" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if( userp(me) && !query("can_perform/qiankun-jian/qian", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(QIAN "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" QIAN "。\n");

        if (me->query_skill("force") < 150)
                return notify_fail("你的內功的修為不夠，難以施展" QIAN "。\n");

        if (me->query_skill("qiankun-jian", 1) < 100)
                return notify_fail("你的乾坤神劍修為不夠，難以施展" QIAN "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠，難以施展" QIAN "。\n");

        if (me->query_skill_mapped("sword") != "qiankun-jian")
                return notify_fail("你沒有激發乾坤神劍，難以施展" QIAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "身形一展，施展乾坤劍法絕技，手中"
              + weapon->name() + HIY "斜斜刺出，劍尖頓時閃出"
              "一道凌厲的青芒，直奔$n" + HIY "而去！\n" NOR;

        ap = me->query_skill("sword");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap / 2);
                addn("neili", -150, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "$n" HIR "見狀連忙格擋，可哪裡來得"
                                           "及，只覺全身一麻，劍氣已透胸而過。\n"
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
