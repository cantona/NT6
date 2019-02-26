#include <ansi.h>
#include <combat.h>

#define YANG "「" HIY "破陽刀" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg, wn;
        object weapon;
        int ap, dp;
  
        me = this_player();

        if( userp(me) && !query("can_perform/poguang-dao/yang", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(YANG "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "blade" )
                return notify_fail("你所使用的武器不對，難以施展" YANG "。\n");

        if ((int)me->query_skill("poguang-dao", 1) < 120)
                return notify_fail("你破光刀法不夠嫻熟，難以施展" YANG "。\n");

        if (me->query_skill_mapped("blade") != "poguang-dao")
                return notify_fail("你沒有激發破光刀法，難以施展" YANG "。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，難以施展" YANG "。\n");

        if( query("neili", me)<400 )
                return notify_fail("你現在的真氣不夠，難以施展" YANG "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        wn = weapon->name();
                           
        msg = HIW "\n$N" HIW "一聲怒喝，內勁瀑漲，施展出絕招「" HIY "破陽刀" HIW 
              "」手中" + wn + HIW "出神般的揮舞而出，雖然招式看似簡單，但其中卻"
              "藴藏着無窮的威力，有如神助一般。" NOR;

        message_sort(msg, me, target);

        ap = me->query_skill("blade");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap + random(ap / 2);
                 msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                          HIR "$n" HIR "見$N" HIR "來勢兇猛，刀"
                                          "光閃爍，驚駭間肩膀已中一刀，一股鮮血" 
                                          "噴湧而出。\n" NOR);
                 me->start_busy(2 + random(4));
                 addn("neili", -200, me);
        } else
        {
                 msg = CYN "然而$n" CYN "以快制快，側身"
                      "一跳，躲過這招。\n" NOR;

                 me->start_busy(2);
                 addn("neili", -180, me);
        }
        message_combatd(msg, me, target);

        return 1;
}


