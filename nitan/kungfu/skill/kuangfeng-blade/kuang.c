// kuang.c -「狂風二十一式」

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "狂風二十一式"; }

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("你只能對戰鬥中的對手使用「狂風二十一式」。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                    return notify_fail("你使用的武器不對！\n");

        if (me->query_skill_mapped("blade") != "kuangfeng-blade")
                return notify_fail("你沒有激發狂風快刀，無法施展。\n");

        if ((int)me->query_skill("kuangfeng-blade", 1) < 150)
                return notify_fail("你目前功力還使不出「狂風二十一式」。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的內力不夠。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        addn("neili", -200, me);
        msg = HIW "\n$N" HIW "淡然一笑，本就快捷絕倫的刀法驟然變"
              "得更加凌厲！就在這一瞬之間，$N" HIW "已劈出二十"
              "一刀！\n刀夾雜着風，風裏含着刀影！$n"
              HIW "只覺得心跳都停止了！\n" NOR;

        if (random(10) < 2)
        {
                if (random(10) < 7) me->start_busy(1);
                else
                {
                        me->start_busy(2);
                }
        }
        ap = attack_power(me, "blade");
        dp = defense_power(target, "dodge");

        if (ap * 3 / 4 + random(ap) > dp)
        {
                if (random(3) == 1) target->start_busy(2);
                damage = damage_power(me, "blade");
                damage += random(damage);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "只見$n" HIR "已被$N" HIR
                                           "切得體無完膚，血如箭般由全身噴射而出！\n" NOR);
        } else
        {
                msg += HIC "可是$p" HIC "急忙抽身躲開，使$P"
                       HIC "這招沒有得逞。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
