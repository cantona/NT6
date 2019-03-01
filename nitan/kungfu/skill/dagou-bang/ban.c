// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "絆字訣" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage, level;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        level = me->query_skill("dagou-bang", 1);

        if (level < 180)
                return notify_fail("你打狗棒法不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("staff") != "dagou-bang")
                return notify_fail("你沒有激發打狗棒法，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 240)
                return notify_fail("你的內功火候不足，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIG "$N" HIG "使出打狗棒法「" NOR + WHT "絆"
              HIG"」字訣，手中"+query("name", weapon)+
              HIG "左封右逼，緩緩朝$n" HIG "挑去。\n" NOR;

        ap = attack_power(me, "staff") + me->query_int()*10;
        dp = defense_power(target, "dodge") + target->query_dex()*10;

        if (ap / 2 + random(ap) > dp)
        {
                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        msg += HIR "$n" HIR "全身一顫，立足不穩，被$N"
                                HIR "這招擊得飛起，重重的跌落在地上。\n" NOR;

                        addn("neili", -50, me);
                        me->start_busy(1);

                        message_combatd(msg, me, target);
                        target->receive_damage("qi", 100, me);
                        set("eff_qi", 1, target);
                        set("eff_jing", 1, target);
                        target->unconcious(me);
                        return 1;
                } else
                {
                        damage = damage_power(me, "staff");
                        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 75,
                                           HIR "只聽$n" HIR "小腿處「嗤嗤」兩聲脆"
                                           "響，竟被$N" HIR "的" + weapon->name() +
                                           HIR "貫出兩個血洞。\n" NOR);
                        me->start_busy(3);
                        addn("neili", -200, me);
                }
        } else
        {
                msg += CYN "可$n" CYN "全神防御，不露半點破綻，使得$N"
                       CYN "這招無功而返。\n" NOR;
                me->start_busy(4);
                addn("neili", -100, me);
        }
        message_combatd(msg, me, target);

        return 1;
}
