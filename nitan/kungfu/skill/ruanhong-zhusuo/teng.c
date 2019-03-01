// tengshe.c 騰蛇訣

#include <ansi.h>
#include <combat.h>

string name() { return WHT "騰蛇訣" NOR; }

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
              query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對，無法施展" + name() + "。\n");

        if ((int)me->query_skill("ruanhong-zhusuo", 1) < 60)
                return notify_fail("你的軟紅蛛索不夠嫻熟，無法施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，無法施展" + name() + "。\n");

        if (me->query_skill_mapped("whip") != "ruanhong-zhusuo")
                return notify_fail("你沒有激發軟紅蛛索，無法施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = WHT "$N" WHT "陡然施展出「騰蛇」訣，手腕輕輕一抖，" + weapon->name() +
              WHT "頓時拔地彈起，如同活物一般悄然襲向$n" + WHT "！\n" NOR;

        ap = attack_power(me, "whip") + me->query_skill("force");
        dp = defense_power(target, "parry") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "whip");
                addn("neili", -150, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "然而$n" HIR "未能看破企圖，一聲慘嚎，"
                                           + weapon->name() + HIR "鞭端已沒入體內半寸"
                                           "，登時連退數步！\n" NOR);
        } else
        {
                addn("neili", -100, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "運足內力，奮力擋住了"
                       CYN "$P" CYN "這神鬼莫測的一擊！\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}