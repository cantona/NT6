// bohu.c 搏虎訣

#include <ansi.h>
#include <combat.h>

string name() { return HIY "搏虎訣" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對，無法施展" + name() + "。\n");

        if ((int)me->query_skill("ruanhong-zhusuo", 1) < 150)
                return notify_fail("你的軟紅蛛索不夠嫻熟，無法施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠，無法施展" + name() + "。\n");

        if (me->query_skill_mapped("whip") != "ruanhong-zhusuo")
                return notify_fail("你沒有激發軟紅蛛索，無法施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$N" HIY "一聲暴喝，使出「搏虎」訣，手中" + weapon->name() +
              HIY "狂舞，漫天鞭影幻作無數小圈，鋪天蓋地罩向$n" + HIY "！\n" NOR;

        ap = attack_power(me, "whip") + me->query_skill("force");
        dp = defense_power(target, "parry") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "whip");
                addn("neili", -300, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           HIR "只聽$n" HIR "一聲慘叫，" + weapon->name() + HIR
                                           "已在$p" + HIR "身上劃出數道深可見骨的傷口，皮肉"
                                           "分離，鮮血飛濺，苦不堪言！\n" NOR);
        } else
        {
                addn("neili", -100, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "運足內力，奮力擋住了"
                       CYN "$P" CYN "這神鬼莫測的一擊！\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}