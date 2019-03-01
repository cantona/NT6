// lian.c 金面生蓮

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "金面生蓮"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「金面生蓮」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("手中沒有劍如何使用「金面生蓮」！\n");

        if( query("neili", me)<250 )
                return notify_fail("你的真氣不夠！\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候不夠！\n");

        if ((int)me->query_skill("miaojia-jian", 1) < 100)
                return notify_fail("你的苗家劍法還不到家，無法使用「金面生蓮」！\n");

        if (me->query_skill_mapped("sword") != "miaojia-jian")
                return notify_fail("你沒有激發苗家劍法，無法使用「金面生蓮」！\n");

        msg = HIG "$N" HIG "手中的" + weapon->name() +
              HIG "一晃，突然化作萬朵金蓮，逼向$n" HIG "，眩人耳目！\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");

                addn("neili", -200, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                           HIR "$n" HIR "眼花繚亂，完全無法看清$N"
                                           HIR "的劍招，一個不慎，連披數劍，血濺五步！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "可是$p" HIC "眼明手快，叮叮當當接連將$P"
                       HIC "的殺招接下，嘆為觀止！\n"NOR;
                addn("neili", -100, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}