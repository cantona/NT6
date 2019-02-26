// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "絕户神抓" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int ap, dp, damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用" + name() + "。\n");

        if( userp(me) && query("shen", me)<10000 )
                return notify_fail(HIC "\n你惡念頓生，剛想施展毒招，可突然想到當初俞蓮舟"
                                   "的一番告誡，不得不中途放棄了攻擊。\n" NOR);

        if ((int)me->query_skill("huzhua-shou", 1) < 120)
                return notify_fail("你的虎爪絕户手不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("claw") != "huzhua-shou")
                return notify_fail("你沒有激發虎爪絕户手，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("claw") != "huzhua-shou")
                return notify_fail("你沒有準備使用虎爪絕户手，無法使用" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIR "$N" HIR "大喝一聲，變掌為爪，雙爪化出漫天爪影，如狂風驟雨一般向$n"
              HIR "的要害抓去！\n" NOR;

        ap = attack_power(me, "claw");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "claw");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "結果$p" HIR "一聲慘嚎，沒能招架住$P"
                                           HIR "凌厲的攻勢，被抓得皮肉分離，鮮血飛濺！\n" NOR);
                addn("neili", -200, me);
                addn("shen", -3000, me);
                me->start_busy(2);
        } else
        {
                me->start_busy(2);
                addn("neili", -100, me);
                addn("shen", -3000, me);
                msg += CYN "可是$p" CYN "看破了$N"
                       CYN "的企圖，躲開了這招殺着。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
