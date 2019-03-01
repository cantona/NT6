#include <ansi.h>
#include <combat.h>

#define CAN "「" RED "殘陽勁" NOR "」"

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/suqin-beijian/can", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(CAN "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" CAN "。\n");

        if (me->query_skill("force") < 80)
                return notify_fail("你的內功的修為不夠，難以施展" CAN "。\n");

        if (me->query_skill("suqin-beijian", 1) < 60)
                return notify_fail("你的蘇秦背劍修為不夠，難以施展" CAN "。\n");

        if (me->query_skill_mapped("sword") != "suqin-beijian")
                return notify_fail("你沒有激發蘇秦背劍，難以施展" CAN "。\n");

        if( query("neili", me)<50 )
                return notify_fail("你現在真氣不夠，難以施展" CAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIR "$N" HIR "伸出兩指，注力于" + weapon->name() +
              HIR "劍脊，驀然回轉劍鋒，攜著全身力道向$n" HIR "劃去。\n" NOR;

        ap = me->query_skill("sword");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 3 + random(ap / 2);
                addn("neili", -30, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 10,
                                           RED "$n" RED "慌忙招架，可已然擋之不及，登"
                                           "時被$N" RED "一劍掃中，鮮血直流！\n" NOR);
        } else
        {
                addn("neili", -20, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "微微一笑，輕輕格擋開了$P"
                       CYN "的劍招。\n"NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}