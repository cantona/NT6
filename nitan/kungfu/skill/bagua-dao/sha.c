#include <ansi.h>
#include <combat.h>


#define SHA "「" HIR "殺龍無悔" NOR "」"

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/bagua-dao/sha", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHA "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對，難以施展" SHA "。\n");

        if (me->query_skill("force") < 250)
                return notify_fail("你的內功修為不夠，難以施展" SHA "。\n");

        if (me->query_skill("bagua-dao", 1) < 180)
                return notify_fail("你的八卦刀法修為不夠，難以施展" SHA "。\n");

        if (me->query_skill_mapped("blade") != "bagua-dao")
                return notify_fail("你沒有激發八卦刀法，難以施展" SHA "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠，難以施展" SHA "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIR "$N" HIR "仰天清嘯，手中" + weapon->name() +
              HIR "斜劃出一道半弧，整個刀身頓時騰起凜冽無比的"
              "殺氣，直貫$n" HIR "而去！\n" NOR;

        ap = attack_power(me, "blade") + me->query_str();
        dp = defense_power(target, "force") + target->query_con();

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                addn("neili", -200, me);
                me->start_busy(3);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           HIR "只聽$n" HIR "一聲慘叫，$N" HIR +
                                           weapon->name() + HIR "刀鋒一閃，竟已嵌"
                                           "入$p" HIR "體內尺許，帶出一蓬血雨。\n"
                                           NOR);
        } else
        {
                addn("neili", -100, me);
                me->start_busy(4);
                msg += CYN "$n" CYN "見$P" CYN "來勢洶湧，不敢輕易抵"
                       "擋，連忙飛身騰挪，躲閃開來。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}