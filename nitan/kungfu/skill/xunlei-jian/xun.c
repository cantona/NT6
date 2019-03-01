#include <ansi.h>
#include <combat.h>

#define XUN "「" HIY "迅雷一擊" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/xunlei-jian/xun", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(XUN "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器無法施展" XUN "。\n");

        if (me->query_skill("force") < 150)
                return notify_fail("你的內功的修為不夠，無法施展" XUN "。\n");

        if (me->query_skill("xunlei-jian", 1) < 100)
                return notify_fail("你的迅雷劍法修為不夠，無法施展" XUN "。\n");

        if( query("neili", me)<250 )
                return notify_fail("你的真氣不夠，無法施展" XUN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "飛身一躍而起，手中" + weapon->name() + NOR + HIY
              "一抖，劍身頓時幻作一道電光，直直射向$n" HIY "而去！\n" NOR;

        ap = me->query_skill("sword");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap / 2);
                addn("neili", -180, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "$n" HIR "躲避不及，劍光頓時透體而"
                                           "入，一聲慘叫，鮮血狂瀉不止。\n" NOR );
        } else
        {
                addn("neili", -60, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "奮力格擋，終于架開了$P"
                       CYN "凌厲的劍招。 \n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}