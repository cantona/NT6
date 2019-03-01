// tui.c 推

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "推天式"; }

int perform(object me, object target)
{
        string msg;
        int skill, ap, dp, damage;

        if (! target || target == me)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("蛤蟆功「推天式」只能對戰鬥中的對手使用。\n");

        skill = me->query_skill("hamagong", 1);

        if (skill < 240)
                return notify_fail("你的蛤蟆功修為不夠精深，不能使用「推天式」！\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你的內力修為不夠深厚，無法施展「推天式」！\n");

        if( query("neili", me)<1000 )
                return notify_fail("你的真氣不夠，無法運用「推天式」！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "蹲在地上，“嗝”的一聲大叫，雙手彎"
              "與肩齊，平推而出，一股極大的力道如同"
              "排山倒海一般奔向$n" HIY "。\n" NOR;

        ap=me->query_skill("force")*15+query("max_neili", me);
        dp=target->query_skill("force")*15+query("max_neili", target)+
             target->query_skill("sun-finger", 1) * 20;
        if (dp < 1) dp = 1;
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -400, me);
                me->start_busy(2);
                damage = damage_power(me, "force");
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 80,
                                           HIR "$n" HIR "奮力低檔，但是$P" HIR "的來勢何"
                                           "等浩大，$p" HIR "登時覺得氣血不暢，“哇”的"
                                           "吐出了一口鮮血。\n" NOR);
        } else
        if (target->query_skill("sun-finger", 1))
        {
                me->start_busy(2);
                addn("neili", -300, me);
                msg += HIG "然而$p" HIG "哈哈一笑，隨手一指刺出，正是一"
                       "陽指的精妙招數，輕易的化解了$P" HIG "的攻勢。\n" NOR;
        } else
        {
                addn("neili", -200, me);
                msg += CYN "可是$n" CYN "將內力運到雙臂上，接下了$P"
                       CYN "這一推之式，只聽“蓬”的一聲，震得四周"
                       "塵土飛揚。\n" NOR;
                me->start_busy(3);
                target->start_busy(1);
                if( query("neili", target)>200 )
                        addn("neili", -200, target);
                else
                        set("neili", 0, target);
        }
        message_combatd(msg, me, target);

        return 1;
}