#include <ansi.h>

inherit F_SSERVER;

string name() { return HIG "無所不為" NOR; }

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

        if (me->query_skill("sanwu-shou", 1) < 70)
                return notify_fail("你的三無三不手級別不夠，無法施展" + name() + "！\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在真氣不夠，無法施展" + name() + "！\n");

        if (me->query_skill_mapped("whip") != "sanwu-shou")
                return notify_fail("你沒有激發三無三不手，無法施展 " + name() + "！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "\n$N暴喝一聲，潛運體內真氣，施出絕招「" HIG "無所不為" HIY
              "」將" + weapon->name() + HIY "揮舞得呼呼直響，\n忽左忽右，將$n"
              HIY "籠罩在" + weapon->name() + "的攻勢之下。" NOR;
        me->start_busy(2);

        message_combatd(msg, me, target);

        ap = attack_power(me, "whip");
        dp = defense_power(target, "dodge");

        if( ap / 2 + random(ap) > dp )
        {
                msg = HIR "$n" HIR "只覺風聲蕭蕭，眼前萬千鞭影，頓感"
                      "手腳無措，驚慌不已。\n" NOR;
                target->start_busy((int)me->query_skill("sanwu-shou") / 80 + 2);
        } else
        {
                msg = CYN "可是$p" CYN "看破了$P"
                      CYN "的企圖，斜跳躲閃開來。\n" NOR;
        }
        addn("neili", -80, me);
        message_combatd(msg, me, target);

        return 1;
}