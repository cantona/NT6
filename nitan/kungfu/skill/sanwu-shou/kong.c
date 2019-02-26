#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "無孔不入" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "whip" )
                return notify_fail("你所使用的武器不對，難以施展" +name()+ "。\n");

        if ((int)me->query_skill("sanwu-shou", 1) < 140)
                return notify_fail("你三無三不手夠嫻熟，難以施展" +name()+ "。\n");

        if (me->query_skill_mapped("whip") != "sanwu-shou")
                return notify_fail("你沒有激發三無三不手，難以施展" +name()+ "。\n");

        if (me->query_skill("force") < 180)
                return notify_fail("你的內功修為不夠，難以施展" +name()+ "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不夠，難以施展" +name()+ "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        ap = attack_power(me, "whip");
        dp = defense_power(target, "parry");

        msg = HIY "\n$N" HIY "一聲長嘯，內勁暴漲，施出絕招「" HIW "無孔"
              "不入" HIY "」手中" + weapon->name() + HIY "哧哧作響，龍"
              "吟不定，\n$N" HIY "猛然騰空而起，揮舞着手中的" + weapon->name() +
              HIY "，凌空直下，湧向$n" HIY "。\n" NOR;
        message_combatd(msg, me, target);

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "whip");

                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "但見$N" HIR "攻勢如洪，氣勢磅礴，"
                                           "$n" HIR "心中略微一驚，慘叫一聲，頓"
                                           "時鮮血淋淋。\n" NOR);

                me->start_busy(2);
                addn("neili", -220, me);
        } else
        {
                msg = CYN "$n" CYN "見$N" CYN "這招襲來，內力"
                      "充盈，只得向後一縱，才躲過這一鞭。\n" NOR;

                me->start_busy(3);
                addn("neili", -100, me);
        }
        message_combatd(msg, me, target);
        return 1;
}
