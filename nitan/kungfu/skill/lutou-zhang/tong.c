#include <ansi.h>
#include <combat.h>

#define TONG "「" HIW "通天徹地" NOR "」"

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;
 
        if( userp(me) && !query("can_perform/lutou-zhang/tong", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(TONG "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不對，難以施展" TONG "。\n");

        if ((int)me->query_skill("force") < 140)
                return notify_fail("你的內功火候不夠，難以施展" TONG "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，難以施展" TONG "。\n");

        if ((int)me->query_skill("lutou-zhang", 1) < 100)
                return notify_fail("你鹿頭杖法火候不夠，難以施展" TONG "。\n");

        if (me->query_skill_mapped("staff") != "lutou-zhang") 
                return notify_fail("你沒有激發鹿頭杖法，難以施展" TONG "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "\n$N" HIW "一聲暴喝，猛然間騰空而起，手中" 
              + weapon->name() + HIW "從天而降，氣勢驚人地"
              "襲向$n" HIW "。\n" NOR;

        message_sort(msg, me, target);

        ap = me->query_skill("staff");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap + random(ap / 2);

                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIR "$n" HIR "完全無法看清招中虛實，只"
                                           "聽「嘭」地一聲，已被$N" HIR "擊中肩膀。\n" NOR);
                me->start_busy(3);
                addn("neili", -180, me);
        } else 
        {
                msg = CYN "可是$n" CYN "奮力招架，左閃右避，好不容"
                       "易抵擋住了$N" CYN "的攻擊。\n" NOR;
                me->start_busy(4);
                addn("neili", -100, me);
        }
        message_vision(msg, me, target);

        return 1;
}