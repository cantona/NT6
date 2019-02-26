// wuji.c 混元無極

#include <ansi.h>
#include <combat.h>

string name() { return HIW "混元無極" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        skill = me->query_skill("hunyuan-zhang", 1);

        if (skill < 120)
                return notify_fail("你的混元掌等級不夠, 不能施展" + name() + "！\n");

        if (me->query_skill("force", 1) < 120)
                return notify_fail("你內功修為不夠，無法施展" + name() + "！\n");

        if( query("max_neili", me)<1400 )
                return notify_fail("你內力修為不足，無法施展" + name() + "！\n");

        if( query("neili", me)<240 )
                return notify_fail("你的內力不夠，無法施展" + name() + "！\n");

        if (me->query_skill_prepared("strike") != "hunyuan-zhang")
                return notify_fail("你沒有準備使用混元掌，無法施展" + name() + "！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIC "$N" HIC "怒喝一聲，潛運「" HIW "混元無極" HIC "」，雙拳挾"
              "着隱隱的風雷之聲向$n" HIC "擊去。\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -220, me);
                damage = damage_power(me, "strike");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "$n" HIR "只覺得胸前一陣劇痛，“哇”的一"
                                           "聲噴出一口鮮血！\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -120, me);
                msg += CYN "只見$n" CYN "不慌不忙，輕輕一閃，躲過"
                       "了$N" CYN "的必殺一擊！\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}