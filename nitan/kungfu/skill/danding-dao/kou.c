#include <ansi.h>
#include <combat.h>

#define KOU "「" HIM "環環相扣" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if( userp(me) && !query("can_perform/danding-dao/kou", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(KOU "只能對戰鬥中的對手使用。\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對，難以施展" KOU "。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，難以施展" KOU "。\n");

        if ((int)me->query_skill("danding-dao", 1) < 80)
                return notify_fail("你的丹碇刀法還不到家，難以施展" KOU "。\n");

        if (me->query_skill_mapped("blade") != "danding-dao")
                return notify_fail("你沒有激發丹碇刀法，難以施展" KOU "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你的真氣不夠，難以施展" KOU "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIM "$N" HIM "刀法忽然一變，時而削，時而砍，時而劈，揮舞如風，轉瞬"
              "即至劈向$n" HIM "！\n" NOR;

        ap = me->query_skill("blade");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap / 2);
                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 35,
                                           HIR "結果$n" HIR "一個不留神，被刀鋒掃"
                                           "到，鮮血四濺，痛徹心肺！\n" NOR);
                me->start_busy(2);
        } else 
        {
                msg += CYN "可是$p" CYN "凝神聚氣，護住門户，無論$P"
                       CYN "怎樣變招，始終奈何不得。\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}