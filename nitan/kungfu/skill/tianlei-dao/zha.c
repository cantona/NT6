#include <ansi.h>
#include <combat.h>

string name() { return HIY "春雷炸空" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg, wn;
        object weapon;
        int ap, dp;

        me = this_player();

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "blade" )
                return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("tianlei-dao", 1) < 150)
                return notify_fail("你天雷絕刀不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "tianlei-dao")
                return notify_fail("你沒有激發天雷絕刀，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        wn = weapon->name();

        msg = HIW "\n$N" HIW "一聲怒喝，內勁瀑漲，施展出絕招「" HIY "春雷炸空" HIW
              "」手中\n" + wn + HIW "出神般的揮舞而出，威力驚人，有如神助一般。" NOR;

        message_combatd(msg, me, target);

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                          HIR "$n" HIR "見$N" HIR "來勢兇猛，刀"
                                          "光閃爍，驚駭間肩膀已中一刀，一股鮮血"
                                          "噴湧而出。\n" NOR);
                me->start_busy(2 + random(2));
                addn("neili", -240, me);
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


