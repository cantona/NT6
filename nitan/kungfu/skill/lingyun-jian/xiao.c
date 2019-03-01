#include <ansi.h>
#include <combat.h>

#define XIAO "「" HIW "劍氣沖霄" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg, wn;
        object weapon;
        int ap, dp;
  
        me = this_player();

        if( userp(me) && !query("can_perform/lingyun-jian/xiao", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(XIAO "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不對，難以施展" XIAO "。\n");

        if ((int)me->query_skill("lingyun-jian", 1) < 120)
                return notify_fail("你凌雲劍法不夠嫻熟，難以施展" XIAO "。\n");

        if (me->query_skill_mapped("sword") != "lingyun-jian")
                return notify_fail("你沒有激發凌雲劍法，難以施展" XIAO "。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候不夠，難以施展" XIAO "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不夠，難以施展" XIAO "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        wn = weapon->name();
                           
        msg = HIW "\n$N" HIW "長嘆一聲，語調宛然，忽然右手斜指長"
              "空，手中" + wn + HIW "寒光閃閃，猛然間使出絕"
              "招「" HIY "劍氣沖霄" HIW "」，剎時間劍風凌厲"
              "，" + wn + HIW "以直沖雲霄之勢，斬向$n\n" HIW "。" NOR;

        message_sort(msg, me, target);

        ap = me->query_skill("sword");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap + random(ap / 2);
                 msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                          HIR "$n" HIR "只見一道金光閃過，心中" 
                                          "驚駭不已，但鮮血已從$n胸口噴出。\n" 
                                          NOR);
                 me->start_busy(2 + random(4));
                 addn("neili", -200, me);
        } else
        {
                 msg = CYN "然而$n" CYN "眼明手快，側身一跳"
                      "躲過$N" CYN "這一劍。\n" NOR;

                 me->start_busy(2);
                 addn("neili", -180, me);
        }
        message_vision(msg, me, target);

        return 1;
}


