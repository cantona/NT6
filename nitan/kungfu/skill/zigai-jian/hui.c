#include <ansi.h>
#include <combat.h>

#define HUI "「" HIC "紫蓋迴翔" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg, wn;
        object weapon;
        int ap, dp;
  
        me = this_player();

//          if (userp(me) && ! me->query("can_perform/zigai-jian/hui"))
//                   return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUI "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不對，難以施展" HUI "。\n");

        if ((int)me->query_skill("zigai-jian", 1) < 120)
                return notify_fail("你紫蓋劍法不夠嫻熟，難以施展" HUI "。\n");

        if (me->query_skill_mapped("sword") != "zigai-jian")
                return notify_fail("你沒有激發紫蓋劍法，難以施展" HUI "。\n");

        if ((int)me->query_skill("force") < 150 )
                return notify_fail("你的內功火候不夠，難以施展" HUI "。\n");
        
        if ((int)me->query_skill("dodge") < 120)
                return notify_fail("你的輕功火候不夠，難以施展" HUI "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你現在的真氣不夠，難以施展" HUI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        wn = weapon->name();
                           
        msg = HIY "\n$N" HIY "撤劍轉身向後一縱，似欲逃走，$n" HIY "乘機挺"
              "劍上前，" HIY "眼見$n" HIY "即\n將得手，不料$N" HIY "凌空"
              "回身反刺，" + wn + HIY "直指$n" HIY "。" NOR;

        message_sort(msg, me, target);
        
        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                 damage = ap + random(ap / 2);

                 msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                          HIR "$n" HIR "心中一驚，雖知中計，但"
                                          + wn + HIR "突如其來迅捷無比，已然閃"
                                          "避不及。\n" NOR);

                 me->start_busy(2);
                 addn("neili", -100, me);
        } else
        {
                 msg = CYN "然而$n" CYN "眼見" + wn + CYN "已至，但$n"
                      CYN "身法迅速無比，提氣向後一縱，$N" CYN "撲了"
                      "個空。\n" NOR;

                 me->start_busy(3);
                 addn("neili", -50, me);
        }
        message_combatd(msg, me, target);

        return 1;
}

