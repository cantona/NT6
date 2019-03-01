// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "若悲" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((int)me->query_skill("mingwang-jian", 1) < 100)
                return notify_fail("你不動明王劍不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "mingwang-jian")
                return notify_fail("你沒有激發不動明王劍，難以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "手中的" + weapon->name() + HIW "輕輕遞出，"
              "發出一陣輕鳴，$n" + HIW "聽了心中不禁有些迷茫。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "心頭一震，一時竟然沉迷當中，忘記了"
                       "繼續攻擊。\n" NOR;
                target->start_busy(ap / 100 + 2);
                me->start_busy(1);
        } else
        {
                msg += HIC "可是$n" HIC "神智只是略微一滯，隨即清醒，沒"
                       "有被$P" HIC "所困擾。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
