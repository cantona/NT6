// This program is a part of NITAN MudLIB
// fugu.c 如蛆附骨

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIW "如蛆附骨" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不對。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧！\n");

        if ((int)me->query_skill("tianshan-zhang", 1) < 60)
                return notify_fail("你的天山杖法不夠嫻熟，不會使用" + name() + "。\n");

        if (me->query_skill_mapped("staff") != "tianshan-zhang")
                return notify_fail("你沒有激發天山杖法，使不了" + name() + "。\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIG "$N" HIG "桀桀奸笑，手中的" + weapon->name() +
              HIG "就像影子一般襲向$n。\n" NOR;

        ap = attack_power(me, "staff");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                msg += HIR "結果$n" HIR "被$N" HIR "嚇得驚慌失措，"
                       "一時間手忙腳亂，難以應對！\n" NOR;

                target->start_busy(ap/100 + 2);
        } else
        {
                msg += "可是$n" HIR "看破了$N" HIR "的企圖，"
                       "輕輕一退，閃去了$N" HIR "的追擊。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
