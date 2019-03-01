// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "伏魔劍訣" NOR; }

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，無法施展" + name() + "。\n");

        if ((int)me->query_skill("yitian-jian", 1) < 120)
                return notify_fail("你的倚天劍法不夠嫻熟，無法施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在真氣不夠，無法施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "yitian-jian")
                return notify_fail("你沒有激發倚天劍法，無法施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "一聲冷哼，手中" + weapon->name() +
              HIW "一振，劍身微顫，聲若龍吟，劍光攜著數個劍花"
              "同時洒向$n" HIW "。\n" NOR;

        addn("neili", -150, me);
        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");
        if (target->is_bad()) ap += ap / 5;


        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90,
                                           (: final, me, target, damage :));
                me->start_busy(2);
        } else
        {
                msg += HIC "可$n" HIC "卻是鎮定逾恆，一絲不亂，"
                       "全神將此招化解開來。\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        return  HIR "只聽$n" HIR "一聲慘叫，被這一劍穿胸而入，頓"
                "時鮮血四處飛濺。\n" NOR;
}