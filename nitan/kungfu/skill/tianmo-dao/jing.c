// jing.c 驚天一擊

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "驚天一擊"; }

int perform(object me)
{
        string msg;
        object weapon, target;
        int ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「驚天一擊」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        ap = attack_power(me, "blade");

        if (ap < 120)
                return notify_fail("你的天魔刀法等級不夠, 不能使用「驚天一擊」！\n");

        if( query("neili", me)<120 )
                return notify_fail("你的真氣不夠，無法運用「驚天一擊」！\n");

        msg = HIY "$N" HIY "一聲冷哼，跨步前移，手中" + weapon->name() +
              HIY "呤呤作響，如閃電般砍向$n" HIY "。\n" NOR;

        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                addn("neili", -80, me);
                damage = damage_power(me, "blade");

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "$n" HIR "看清來招，飛身閃躲，然而$N"
                                           HIR "忽而招式一變，手中" + weapon->name() +
                                           HIR "斜上揮向$n" HIR "的雙腿。\n"
                                           HIR "只聽$n" HIR "連聲慘呼，已被砍中，點點血"
                                           HIR "滴如雨點般漫天洒下。\n" NOR);
                me->start_busy(1 + random(3));
        } else
        {
                addn("neili", -30, me);
                msg += HIC "可是$n" HIC "早已看清$N"
                       HIC "的企圖，輕巧地將$P" HIC "的來招架開。\n"NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}
