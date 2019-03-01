#include <ansi.h>
#include <combat.h>

#define GUI "「" HIY "天地歸元" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if( userp(me) && !query("can_perform/yuanshi-jian/gui", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(GUI "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" GUI "。\n");

        if ((int)me->query_skill("yuanshi-jian", 1) < 140)
                return notify_fail("你的原始劍法不夠嫻熟，難以施展" GUI "。\n");

        if( query("neili", me)<400 )
                return notify_fail("你的真氣不夠，難以施展" GUI "。\n");

        if (me->query_skill_mapped("sword") != "yuanshi-jian")
                return notify_fail("你沒有激發原始劍法，難以施展" GUI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "運轉內勁，手中" + weapon->name() + HIY "頓時青光閃"
              "爍，出劍嗤然有聲，朝$n" HIY "電射而去！\n" NOR;

        ap = me->query_skill("sword");
        dp = target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2;
                damage = damage + random(damage);

                addn("neili", -250, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                           HIR "只見$N" HIR + weapon->name() + HIR
                                           "劍芒暴長，$p" HIR "霎時只覺一股熱流穿"
                                           "心而過，嘔出一口鮮血。\n" NOR);
                me->start_busy(2);
        } else 
        {
                msg += CYN "可是$n" CYN "猛地向前一躍，跳出了$N"
                       CYN "的攻擊范圍。\n"NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}