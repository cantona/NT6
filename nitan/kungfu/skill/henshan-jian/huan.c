#include <ansi.h>
#include <combat.h>

#define HUAN "「" HIW "幻劍式" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg, wn;
        object weapon;
        int ap, dp;
  
        me = this_player();

        if( userp(me) && !query("can_perform/henshan-jian/huan", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUAN "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不對，難以施展" HUAN "。\n");

        if ((int)me->query_skill("henshan-jian", 1) < 60)
                return notify_fail("你衡山劍法不夠嫻熟，難以施展" HUAN "。\n");

        if (me->query_skill_mapped("sword") != "henshan-jian")
                return notify_fail("你沒有激發衡山劍法，難以施展" HUAN "。\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的內功火候不夠，難以施展" HUAN "。\n");

        if( query("neili", me)<50 )
                return notify_fail("你現在的真氣不夠，難以施展" HUAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        wn = weapon->name();
                           
        msg = HIC "\n$N" HIC "將真氣運於劍身，身法陡然加快，手中" + wn +
              HIC "劍隨人動，霎那間劍光四散，如夢如幻，像有無數柄" + wn +
              HIC "一齊襲向$n" HIC "。" NOR;

        message_sort(msg, me, target);

        ap = me->query_skill("sword");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 3 + random(ap / 2);
                 msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 10,
                                          HIR "$n" HIR "看得眼花繚亂，卻分不清"
                                          "劍的來路，肩膀已被" + wn + HIR "刺出"
                                          "一個窟窿。\n" NOR);
                 me->start_busy(2);
                 addn("neili", -50, me);
        } else
        {
                 msg = CYN "然而$n" CYN "並未受幻象所困，側身一跳"
                      "躲過$N" CYN "這一劍。\n" NOR;

                 me->start_busy(2);
                 addn("neili", -30, me);
        }
        message_combatd(msg, me, target);

        return 1;
}

