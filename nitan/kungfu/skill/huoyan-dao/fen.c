// This program is a part of NITAN MudLIB
// fen.c 焚身

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "焚身"; }
int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「焚身」只能對戰鬥中的對手使用。\n");

        skill = me->query_skill("huoyan-dao", 1);

        if (skill < 120)
                return notify_fail("你的火燄刀等級不夠，還不能使出「焚身」！\n");

        if (me->query_skill("force") < 120)
                return notify_fail("你的內功火候不夠，不能使用這樣絕技。\n");

        if( query("neili", me)<400 )
                return notify_fail("你的內力不夠，無法運功！\n");

        if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIR "$N" HIR "聚氣于掌，使出一招「焚身」，無形刀氣向$n"
              HIR "的胸口擊去。\n"NOR;

        ap = attack_power(me, "force");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -300, me);
                damage = damage_power(me, "force");
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 50,
                                           HIR "$p" HIR "強運內力試圖抵抗，然而無法掌握$P"
                                           HIR "內力的變化，結果被$P"
                                           HIR "的無形刀氣重創在胸口！\n" NOR);
                me->start_busy(2);

        } else
        {
                msg += HIC "卻見$p" HIC "不慌不忙，輕輕一閃，躲過了$P"
                       HIC "的必殺一擊！\n" NOR;
                addn("neili", -150, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
