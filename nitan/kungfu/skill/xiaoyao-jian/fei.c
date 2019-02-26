// This program is a part of NT MudLIB
#include <ansi.h>
#include <combat.h>

string name() { return HIW "飛劍訣" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg, wn;
        object weapon;
        int level;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if (! objectp(weapon = query_temp("weapon", me)) ||
            (string)query("skill_type", weapon) != "sword")
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((int)me->query_skill("xiaoyao-jian", 1) < 60)
                return notify_fail("你逍遙劍法不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "xiaoyao-jian")
                return notify_fail("你沒有激發逍遙劍法，難以施展" + name() + "。\n");

        if (me->query_skill("dodge") < 150)
                return notify_fail("你的輕功修為不夠，難以施展" + name() + "。\n");

        if ((int)query("neili", me) < 200)
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        wn = weapon->name();

        msg = HIC "\n$N" HIC "陡然身法奇快，劍法靈動無比，手中" + wn + HIC "猶"
              "如脱手飛旋一般，將$n" HIC "周身籠罩。\n" NOR;

        message_combatd(msg, me, target);

        level = me->query_skill("sword");

        addn("neili", -120, me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIY "$N" HIY "看不出$n" HIY "招式中的虛實，連忙"
                      "護住自己全身，一時竟無以應對！\n" NOR;
                target->start_busy(4 + random(level / 25));
                me->start_busy(random(2));
        } else
        {
                msg = CYN "可是$N" CYN "鎮定自若，小心拆招，沒有被"
                      "$n" NOR + CYN "招式所困。\n" NOR;

                me->start_busy(2);
        }
        message_combatd(msg, target, me);

        return 1;
}