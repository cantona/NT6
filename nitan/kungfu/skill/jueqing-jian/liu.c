#include <ansi.h>
#include <combat.h>

#define LIU "「" HIR "流水無情" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg, wn;
        object weapon;
        int ap, dp;
  
        me = this_player();

        if( userp(me) && !query("can_perform/jueqing-jian/liu", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LIU "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不對，難以施展" LIU "。\n");

        if ((int)me->query_skill("jueqing-jian", 1) < 60)
                return notify_fail("你絕情劍法不夠嫻熟，難以施展" LIU "。\n");

        if (me->query_skill_mapped("sword") != "jueqing-jian")
                return notify_fail("你沒有激發絕情劍法，難以施展" LIU "。\n");

        if ((int)me->query_skill("force") < 80 )
                return notify_fail("你的內功火候不夠，難以施展" LIU "。\n");
        
        if( query("neili", me)<60 )
                return notify_fail("你現在的真氣不夠，難以施展" LIU "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        wn = weapon->name();

        msg = HIY "\n$N" HIY "長歎一聲，一股悲切之情湧上心頭，手中" + wn +
              HIY "迅猛無比地刺出，風聲嗖嗖，完全不理會$n" HIY "的攻勢，"
              "將自己的生死置之度外，這正是絕情谷絕學「" HIR "流水無情" HIY
              "」。" NOR; 

        message_sort(msg, me, target);
        
        ap = me->query_skill("jueqing-jian", 1);
        dp = target->query_skill("parry", 1);

        if (ap / 2 + random(ap) > dp)
        {
                 damage = ap + random(ap / 4);

                 msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 24,
                                          HIR "$n" HIR "見$N" HIR "此招劍勢迅"
                                          "猛，似與自己共存亡，心中一驚，早已中"
                                          "劍。\n" NOR);

                 me->start_busy(1+random(2));
                 addn("neili", -60, me);
        } else
        {
                 msg = CYN "然而$n" CYN "眼見" + wn + CYN "已至，但$n"
                      CYN "身法迅速無比，提氣向後一縱，$N" CYN "撲了"
                      "個空。\n" NOR;

                 me->start_busy(2);
                 addn("neili", -30, me);
        }
        message_combatd(msg, me, target);

        return 1;
}


