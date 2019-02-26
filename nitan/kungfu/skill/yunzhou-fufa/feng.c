#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "風魔舞" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放"
                                   "膽攻擊吧。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "whip" )
                return notify_fail("你的武器不對，無法施展" + name() + "\n");

        if (me->query_skill("yunzhou-fufa", 1) < 60)
                return notify_fail("你的雲帚拂法級別不夠，無法施展" + name() + "！\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在真氣不夠，無法施展" + name() + "！\n");

        if (me->query_skill_mapped("whip") != "yunzhou-fufa")
                return notify_fail("你沒有激發雲帚拂法，無法施展" + name() + "！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "\n$N暴喝一聲，潛運體內真氣，將" + weapon->name() + HIY
              "揮舞得呼呼直響，直破長空，猶如漫天狂沙般卷向$n。\n" NOR;

        ap = attack_power(me, "whip");
        dp = defense_power(target, "dodge");

        if( ap / 2 + random(ap) > dp )
        {
                msg += HIR "$n" HIR "只覺風聲蕭蕭，眼前萬千鞭影，頓感"
                      "手腳無措，驚慌不已。\n" NOR;

                target->start_busy((int)me->query_skill("yunzhou-fufa") / 25 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P"
                      CYN "的企圖，斜跳躲閃開來。\n" NOR;
        }
        me->start_busy(1);

        addn("neili", -80, me);
        message_combatd(msg, me, target);

        return 1;
}