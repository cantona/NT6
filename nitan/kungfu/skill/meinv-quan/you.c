// This program is a part of NITAN MudLIB
// you.c 古墓幽居

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "古墓幽居" NOR; }

int perform(object me, object target)
{
        int damage, ap, dp;
        string msg;
        string pmsg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if (me->query_temp("weapon"))
                return notify_fail("你必須空手才能施展" + name() + "。\n");

        if ((int)me->query_skill("meinv-quan", 1) < 80)
                return notify_fail("你的美女拳法別不夠，不會使用" + name() + "。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功還未嫻熟，不能使用" + name() + "。\n");

        if ((int)me->query("neili") < 180)
                return notify_fail("你現在真氣不夠，不能使用" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "meinv-quan")
                return notify_fail("你沒有激發美女拳法，不能施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "meinv-quan")
                return notify_fail("你沒有準備美女拳法，難以施展" + name() + "。\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "\n$N" HIW "右手支頤，左袖輕輕揮出，長歎一聲，使"
              "出古墓派絕學「古墓幽居」，一臉盡現寂寥之意。\n" NOR;

        ap = attack_power(me, "unarmed");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1+random(2));

                damage = damage_power(me, "unarmed");

                addn("neili", -100, me);

                if (damage < 30)
                        pmsg = HIY "結果$n" HIY "被$N袍"
                               HIY "袖一拂，悶哼一聲。\n" NOR;
                else if(damage < 55)
                        pmsg = HIY "結果$n" HIY "被$N"
                               HIY "以袍袖一拂，「騰騰」地退出幾步。\n" NOR;
                else if (damage < 80)
                        pmsg = HIR "結果$n" HIR "被$N"
                               HIR "以袍袖一拂，胸口有如受到一記重"
                               "錘，氣血為之一窒！\n" NOR;
                else if (damage < 100)
                        pmsg = RED "結果$n" RED "被$N" RED
                               "的袍袖一拂，眼前一黑，渾身氣血翻騰，"
                               "竟如身入洪爐一般！\n" NOR;
                else
                        pmsg = HIR "但見$N" HIR "雙拳襲來，柔中帶剛，迅"
                               "猛無比，其間彷彿藴藏着無窮的威力，$n" HIR
                               "正遲疑間，卻已中拳，悶哼一聲，倒"
                               "退幾步，一口鮮血噴出。\n" NOR;

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50, pmsg);
        } else
        {
                me->start_busy(3);
                msg += CYN "可是$p" CYN "看破了$P" CYN
                       "的企圖，穩如泰山，抬手一架格開了$P"
                       CYN "這一拳。\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}