// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "般若極" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp, shd, jia, layer, damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("longxiang-gong", 1) < 300)
                return notify_fail("你的龍象般若功修為不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "longxiang-gong")
                return notify_fail("你沒有激發龍象般若功為拳腳，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "longxiang-gong")
                return notify_fail("你沒有激發龍象般若功為內功，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "longxiang-gong")
                return notify_fail("你沒有準備使用龍象般若功，難以施展" + name() + "。\n");

        if( query("neili", me)<800 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        layer = me->query_skill("longxiang-gong", 1) / 30;

        if (layer > 13) layer = 13;

        msg = HIY "$N" HIY "運轉龍象般若功第" + chinese_number(layer) + "層"
              "功力，雙拳攜着『" HIR "十龍十象" HIY "』之力朝$n" HIY "崩擊"
              "\n而出，拳鋒過處，竟捲起萬里塵埃，正是密宗絕學「" HIW "般若"
              "極" HIY "」。\n" NOR;

        ap = attack_power(me, "unarmed") + me->query_skill("force");
        dp = defense_power(target, "parry") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                if( query_temp("shield", target) )
                {
                        shd=query_temp("apply/armor", target);

                        addn_temp("apply/armor", -shd, target);
                        delete_temp("shield", target);

                        msg += HIW "$N" HIW "罡氣湧至，竟然激起層層氣浪，頓時將$n"
                               HIW "的護體真氣摧毀得蕩然無存！\n" NOR;
                }
                jia=query("jiali", me);
                damage = damage_power(me, "unarmed");
                damage+= jia;

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 65,
                                               HIR "$n" HIR "不及閃避，頓被$N" HIR
                                               "雙拳擊個正中，般若罡勁破體而入，盡"
                                               "傷三焦六脈。\n" NOR);

                me->start_busy(5);
                addn("neili", -800, me);
        } else
        {
                me->start_busy(5);
                addn("neili", -500, me);
                msg += CYN "可是$p" CYN "識破了$P"
                       CYN "這一招，斜斜一躍避開。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
