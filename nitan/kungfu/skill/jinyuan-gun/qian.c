#include <ansi.h>
#include <combat.h>

#define QIAN "「" HIY "乾坤一擊" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if( userp(me) && !query("can_perform/jinyuan-gun/qian", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(QIAN "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "club" )
                return notify_fail("你使用的武器不對，難以施展" QIAN "。\n");

        if (me->query_skill("force") < 180)
                return notify_fail("你的內功的修為不夠，難以施展" QIAN "。\n");

        if (me->query_skill("jinyuan-gun", 1) < 120)
                return notify_fail("你的金猿棍法修為不夠，難以施展" QIAN "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，難以施展" QIAN "。\n");

        if (me->query_skill_mapped("club") != "jinyuan-gun")
                return notify_fail("你沒有激發金猿棍法，難以施展" QIAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "大步上前，怒吼一聲，手中" + weapon->name() +
              HIY "急速舞動，霎時間飛沙走石，罡氣激盪。\n便在狂沙颶風中"
              "，$N" HIY "忽然高高躍起，迎頭一棒朝$n" HIY "劈落！\n" NOR;

        ap = me->query_skill("club");
        dp = target->query_skill("dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap * 2 / 3);
                addn("neili", -150, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 35,
                                           HIR "$n" HIR "渾身被勁風籠罩，登感窒息"
                                           "，“哇”的吐出一口鮮血，仰面便倒！\n" NOR);
        } else
        {
                addn("neili", -100, me);
                me->start_busy(3);
                msg += CYN "$n" CYN "不敢有絲毫大意，急忙縱身後躍，躲"
                       "開這足以斷金裂石的一擊。\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}