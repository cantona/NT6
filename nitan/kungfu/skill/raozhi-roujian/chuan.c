// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "柔月穿空"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「柔月穿空」只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的內功的修為不夠，使不出「柔月穿空」這一招！\n");

        if (me->query_skill("raozhi-roujian", 1) < 120)
                return notify_fail("你的繞指柔劍修為不夠，使不出「柔月穿空」這一招！\n");

        if( query("neili", me)<250 )
                return notify_fail("你的真氣不夠，不能使用佛心劍！\n");

        msg = HIM "$N" HIM "猛地裡一聲清嘯，劍法忽變，那柄" + weapon->name() + HIM
                  "竟似成了一條軟帶，輕柔曲折，飄忽不定，正是武當派的\n"
                  "七十二招「繞指柔劍」中的一招「柔月穿空」。只見$N"
                  HIM + weapon->name() + HIM "劍破長空，疾刺$n" HIM "胸膛，"
                  "劍到中途，\n劍尖微顫，竟然彎了過去，斜刺$p" HIM "右肩。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -150, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "結果$n" HIR "一個不慎，被$N" HIR
                                           "精妙的劍招刺中，一聲慘嚎，鮮血飛濺而出！\n" NOR);
        } else
        {
                addn("neili", -60, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "並不慌亂，收斂心神，輕輕格擋開了$P"
                       CYN "的劍招。\n"NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}
