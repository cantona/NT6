#include <ansi.h>
#include <combat.h>

#define LUO "「" HIW "落雷式" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg, wn;
        object weapon;
        int ap, dp;
  
        me = this_player();

        if( userp(me) && !query("can_perform/zilei-jian/luo", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LUO "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不對，難以施展" LUO "。\n");

        if ((int)me->query_skill("zilei-jian", 1) < 120)
                return notify_fail("你紫雷劍法不夠嫻熟，難以施展" LUO "。\n");

        if (me->query_skill_mapped("sword") != "zilei-jian")
                return notify_fail("你沒有激發紫雷劍法，難以施展" LUO "。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，難以施展" LUO "。\n");

        if( query("neili", me)<400 )
                return notify_fail("你現在的真氣不夠，難以施展" LUO "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        wn = weapon->name();
                           
        msg = HIW "\n$N" HIW "將" + wn + HIW "斜指長空，猛地飛身躍起，"
              + wn + HIW "長響一聲，寒光閃閃，猶如一道閃電劈空而下，一招"
              "「" HIG "落雷式" HIW "」已使出，以千軍不可擋之勢襲向$n" HIW 
              "。" NOR;

        message_sort(msg, me, target);

        ap = me->query_skill("sword");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap + random(ap / 2);
                 msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                          HIR "$n" HIR "只見一道電光從半空襲來，"
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
        message_combatd(msg, me, target);

        return 1;
}

