#include <ansi.h>
#include <combat.h>

#define HAO "「" HIW "皓月穿空" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg, wn;
        object weapon;
        int ap, dp;
  
        me = this_player();

        if( userp(me) && !query("can_perform/chuanyue/hao", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HAO "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不對，難以施展" HAO "。\n");

        if ((int)me->query_skill("chuanyue-jian", 1) < 120)
                return notify_fail("你紫雷劍法不夠嫻熟，難以施展" HAO "。\n");

        if (me->query_skill_mapped("sword") != "chuanyue-jian")
                return notify_fail("你沒有激發紫雷劍法，難以施展" HAO "。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，難以施展" HAO "。\n");

        if( query("neili", me)<400 )
                return notify_fail("你現在的真氣不夠，難以施展" HAO "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        wn = weapon->name();
                           
        msg = HIY "\n$N" HIY "將手中" + wn + HIY "反轉幾周，然後"
              "猛地騰空而起，施出絕招「" HIW "皓月穿空" HIY "」，"
              "“皓月熒熒掛長空，利劍盈盈斬群雄。”。手中劍光瀑"
              "漲，氣勢磅礡，半空直下，襲向$n\n " HIY "。" NOR;

        message_sort(msg, me, target);

        ap = me->query_skill("sword");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap + random(ap / 2);
                 msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 48,
                                          HIR "$n" HIR "只見一道劍光從半空襲來，"
                                          "心中驚駭不已，但鮮血已從$n胸口噴出。\n" 
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

