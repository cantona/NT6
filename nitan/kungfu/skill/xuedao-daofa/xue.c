// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "祭血神刀" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 220)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("xuedao-daofa", 1) < 160)
                return notify_fail("你的血刀大法還不到家，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "xuedao-daofa")
                return notify_fail("你沒有激發血刀大法為刀法，難以施展" + name() + "。\n");

        if( query("qi", me)<100 )
                return notify_fail("你目前氣血翻滾，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你目前真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        ap = attack_power(me, "blade");
        dp = defense_power(target, "force");

        msg = HIR "$N" HIR "揮刀向左肩一勒，血珠頓時濺滿刀面，緊接着右臂"
              "掄出一片血光向$n" HIR "當頭劈落。\n" NOR;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                damage+= query("jiali", me);
                addn("neili", -150, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                           HIR "$n" HIR "只見血刀疾閃，眼前一陣血"
                                           "紅，刀刃劈面而下，鮮血飛濺，不禁慘聲"
                                           "大嚎！\n" NOR);
        } else
        {
                me->start_busy(3);
                msg += CYN "可是$n" CYN "側身避讓，不慌不忙，躲過了$N"
                       CYN "的必殺一刀。\n"NOR;
                addn("neili", -100, me);
        }
        me->receive_wound("qi", 50);
        message_combatd(msg, me, target);
        return 1;
}
