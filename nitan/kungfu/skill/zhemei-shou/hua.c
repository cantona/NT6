// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

string name() { return HIR "化妖功" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp, p;
        int lv, cost_neili;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("beiming-shengong", 1) < 220
        &&  (int)me->query_skill("xiaowuxiang", 1) < 220
        &&  (int)me->query_skill("bahuang-gong", 1) < 220)
                return notify_fail("你的北冥神功火候不夠，難以施展" + name() + "。\n");

        if (lv = (int)me->query_skill("zhemei-shou", 1) < 220)
                return notify_fail("你逍遙折梅手等級不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if( query("neili", me)<800 )
                return notify_fail("你現在真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIM "$N" HIM "深深吸進一口氣，單手揮出，掌緣頓時霞光萬道，漾出"
              "七色虹彩向$n" HIM "席捲而至。\n" NOR;

        ap = attack_power(me, "hand") + me->query_skill("dodge");
        dp = defense_power(target, "parry") + target->query_skill("dodge");

        if (target->is_bad() || ! userp(target))
                ap += ap / 10;

        if (ap / 2 + random(ap) > dp)
        {
                damage = 0;
                lv = me->query_skill("zhemei-shou", 1);
                if (lv >= 220)cost_neili = -500;
                if (lv >= 240)cost_neili = -470;
                if (lv >= 260)cost_neili = -440;
                if (lv >= 280)cost_neili = -400;
                if (lv >= 300)cost_neili = -360;
                if (lv >= 320)cost_neili = -320;
                if (lv >= 340)cost_neili = -300;
                if (lv >= 360)cost_neili = -270;
                if (lv >= 400)cost_neili = -200;
                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        msg += HIM "只聽$n" HIM "一聲尖嘯，$N" HIM "的七色掌"
                               "勁已盡數注入$p" HIM "體內，頓時將$p" HIM "化"
                               "為一灘血水。\n" NOR "( $n" RED "受傷過重，已"
                               "經有如風中殘燭，隨時都可能斷氣。" NOR ")\n";
                        damage = -1;
                        addn("neili", cost_neili, me);
                        me->start_busy(1);
                } else
                {
                        damage = damage_power(me, "hand");
                        damage+=query("jiali", me);
                        damage+=query_temp("apply/unarmed_damage", me);
                        damage+=query_temp("apply/damage1", me);

                        target->receive_damage("qi", damage, me);
                        target->receive_wound("qi", damage / 2, me);
                        target->receive_damage("jing", damage / 4, me);
                        target->receive_wound("jing", damage / 8, me);
                        p=query("qi", target)*100/query("max_qi", target);

                        msg += HIM "$n" HIM "只是微微一愣，$N" HIM "的七色掌勁已破體而"
                               "入，$p" HIM "便猶如身置洪爐一般，連嘔數口鮮血。\n" NOR;
                        msg += "( $n" + eff_status_msg(p) + " )\n";

                        addn("neili", cost_neili, me);
                        me->start_busy(3);
                }
        } else
        {
                msg += CYN "$p" CYN "見狀大驚失色，完全勘破不透$P"
                       CYN "招中奧祕，當即飛身躍起丈許，躲閃開來。\n" NOR;
                addn("neili", -200, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        if (damage < 0)
        {
                target->receive_damage("qi", 100, me);
                target->unconcious(me);
        }

        return 1;
}