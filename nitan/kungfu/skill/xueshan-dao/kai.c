#include <ansi.h>
#include <combat.h>

#define KAI "「" HIW "冰河開封" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if( userp(me) && !query("can_perform/xueshan-dao/kai", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(KAI "只能對戰鬥中的對手使用。\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對，難以施展" KAI "。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，難以施展" KAI "。\n");

        if ((int)me->query_skill("xueshan-dao", 1) < 80)
                return notify_fail("你的雪山刀法還不到家，難以施展" KAI "。\n");

        if (me->query_skill_mapped("blade") != "xueshan-dao")
                return notify_fail("你沒有激發雪山刀法，難以施展" KAI "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你的真氣不夠，難以施展" KAI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "只見$N" HIW "手中的" + weapon->name() +  HIW "豪光綻放，嗡"
              "嗡作響，刀鋒頓時迸出一道寒芒向$n" HIW "砍落！\n" NOR;

        ap = me->query_skill("blade");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap / 2);
                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 35,
                                           HIR "$n" HIR "招架不及，頓時被$N" HIR
                                           "凌厲的刀芒劃中要害，鮮血狂濺而出！\n" NOR);
                me->start_busy(2);
        } else 
        {
                msg += CYN "可是$p" CYN "凝神聚氣，護住門戶，$P"
                       CYN "刀芒雖然凌厲，始終奈何不得。\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}