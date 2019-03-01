#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "寒冰針" NOR; }

#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
        int skill, n;
        int ap, dp, p, damage;
        string msg, pmsg;
        object weapon;
        int level;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("handing", me)) ||
            query("skill_type", weapon) != "throwing" )
                return notify_fail("你現在手中沒有拿著暗器，難以施展" + name() + "。\n");

        if (weapon->query_amount() < 1)
                return notify_fail("你手中沒有針，無法施展" + name() + "。\n");

        if ((skill = me->query_skill("bingpo-shenzhen", 1)) < 120)
                return notify_fail("你的冰魄神針不夠嫻熟，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功修為不足，難以施展" + name() + "。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你現在真氣不足，難以施展" + name() + "。\n");

        if( query_temp("bingpo", target) )
                return notify_fail("對方已經中了你的絕招，現在是廢人一"
                                   "個，趕快進攻吧！\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        addn("neili", -120, me);
        weapon->add_amount(-1);

        msg = HIY "只見$N" HIY "長袖微拂，手腕一轉，一招「" HIW "寒冰針"
              HIY"」，將手中" + weapon->name() + HIY "猛地射出。剎那\n"
              "間，長空破響，" + weapon->name() + HIY "如同一顆流星劃過，"
              "襲向$n！\n" NOR;

        ap = attack_power(me, "throwing");
        dp = defense_power(target, "dodge");
        level = skill;

        if (ap + random(ap / 2) > dp)
        {
                damage = damage_power(me, "throwing");
                if (target->query_skill("parry") < me->query_skill("throwing"))
                {

                        msg += HIR "只聽$n" HIR "慘叫一聲，" + weapon->name() + HIR
                               "已經射中要害，只感傷口處透處陣陣寒意，頓覺全身軟"
                               "弱無力。\n"NOR;

                        target->receive_damage("qi", damage, me);
                        target->receive_wound("qi", damage/ 3, me);
                        set_temp("bingpo", 1, target);
                        addn_temp("apply/attack", -level/5, target);
                        addn_temp("apply/dodge", -level/5, target);
                        addn_temp("apply/parry", -level/10, target);
                        target->set_weak(3, 0);

                        COMBAT_D->clear_ahinfo();
                        weapon->hit_ob(me,target,query("jiali", me)+180);

                        p=query("qi", target)*100/query("max_qi", target);

                        if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                                 msg += pmsg;

                        msg += "( $n" + eff_status_msg(p) + " )\n";

                        message_combatd(msg, me, target);

                        tell_object(target, RED "你現在要穴受到重損，乃至全身乏力"
                                            "，提不上半點力道！\n" NOR);
                        tell_object(me, HIC "你心知剛才這招已打中對方要害，不禁暗自冷笑。\n" NOR);
                        call_out("back", 2 + random(skill / 15), target, level);
                } else
                {
                        msg += HIR "$n" HIR "眼見暗器襲來，左躲右閃，但仍"
                               "然受了一點輕傷。\n" NOR, me, target;

                        target->receive_damage("qi", damage/2);
                        target->receive_wound("qi", damage/4);
                        COMBAT_D->clear_ahinfo();
                        weapon->hit_ob(me,target,query("jiali", me)/2);
                        p=query("qi", target)*100/query("max_qi", target);

                        msg += "( $n" + eff_status_msg(p) + " )\n";

                        message_combatd(msg, me, target);

                        tell_object(target, RED "你只覺全身幾處一陣刺痛，知道自己"
                                            "雖被擊中，但卻是避開了要害。\n" NOR);
                        me->start_busy(1 + random(2));
                }
        } else
        {        msg += CYN "可是$n" CYN "身法靈巧，小心閃避，好不容易避開了"
                                 CYN "$N" CYN "迅猛如電的攻擊。\n" NOR;
                 message_combatd(msg, me, target);
                 me->start_busy(3);
        }
        return 1;
}

void back(object target, int level)
{
        if (objectp(target))
        {
                addn_temp("apply/attack", level/5, target);
                addn_temp("apply/dodge", level/5, target);
                addn_temp("apply/parry", level/10, target);
                // tell_object(target, HIY "漸漸的你覺得力氣一絲絲的恢復了。\n" NOR);
                delete_temp("bingpo", target);
        }
}
