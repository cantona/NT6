// chuanxin.c 一劍穿心

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "一劍穿心"; }

int perform(object me)
{
        string msg;
        object weapon, target;
        int ap, dp, damage, exp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「一劍穿心」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        ap = attack_power(me, "sword");

        if (ap < 250)
                return notify_fail("你的天魔劍法等級不夠, 不能使用「一劍穿心」！\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠，無法運用「一劍穿心」！\n");

        msg = HIC "$N" HIC "一聲長嘯，雙足一點已縱身而起，身子急轉數圈，與手中的"
              + weapon->name() + HIC + "合為一體，化作一道白光，如箭離弦一般筆直向$n" HIC
              "射來。\n" NOR;

        dp = defense_power(target, "force");
        exp=query("combat_exp", me)/query("combat_exp", target);

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                addn("neili", -220, me);
                damage = damage_power(me, "sword") + (int)me->query_skill("xixing-dafa", 1);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                           HIR "$n" HIR "只覺前胸“撲哧”一聲，已被"
                                           "洞穿而過，一股血箭疾射而出，不禁一聲慘嚎！\n" NOR);
                me->start_busy(2);
                if (exp > 3)
                {
                      message_combatd(msg, me, target);
                      target->die(me);
                      return 1;
                }
        } else
        {
                addn("neili", -60, me);
                msg += HIG "可是$n" HIG "早有防備，身形一轉，已避開了$N"
                       HIG "的全力一擊。\n"NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}
