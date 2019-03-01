#include <ansi.h>
#include <combat.h>

#define YING "「" HIC "刀影重重" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/hanwang-qingdao/ying", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(YING "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對，難以施展" YING "。\n");

        if (me->query_skill("force") < 120)
                return notify_fail("你的內功的修為不夠，難以施展" YING "。\n");

        if (me->query_skill("hanwang-qingdao", 1) < 80)
                return notify_fail("你的韓王青刀修為不夠，難以施展" YING "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你目前的內力不足，難以施展" YING "。\n");

        if (me->query_skill_mapped("blade") != "hanwang-qingdao")
                return notify_fail("你沒有激發韓王青刀，難以施展" YING "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIC "霎時只見$N" HIC "手中" + weapon->name() +
              HIC "一振，頓時幻出重重刀影，將$n" HIC "團團裹住！\n" NOR;

        ap = me->query_skill("blade");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 3 + random(ap / 3);
                me->start_busy(1);
                addn("neili", -80, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 20,
                                           HIR "只聽$p" HIR "一聲慘嚎，一股血柱自" HIR
                                           "血色刀影中激射而出！\n" NOR);
        } else
        {
                addn("neili", -40, me);
                me->start_busy(3);
                msg += CYN "可是$n" CYN "淡淡一笑，渾然不將$N"
                       CYN "重重刀影放在眼中，隨意將之架開。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}