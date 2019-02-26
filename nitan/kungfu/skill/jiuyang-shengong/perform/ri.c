// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;

string name() { return HIW "魔光日無極" NOR; }

int perform(object me)
{
        object *obs;
        string msg;
        int damage;
        int ap, dp;
        int flag;
        int i;
        int p;

        me->clean_up_enemy();
        if (! me->is_fighting())
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail(name() + "只能空手施展。\n");

        if (query("max_neili", me) < 8000)
                return notify_fail("你的內力的修為不夠，現在無法使用" + name() + "。\n");

        if (me->query_skill("jiuyang-shengong", 1) < 250)
                return notify_fail("你的九陽神功還不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "jiuyang-shengong")
                return notify_fail("你現在沒有激發九陽神功為拳腳，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("你現在沒有激發九陽神功為內功，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "jiuyang-shengong")
                return notify_fail("你現在沒有準備使用九陽神功，難以施展" + name() + "。\n");

        if ((int)query("neili", me) < 2000)
                return notify_fail("你的真氣不夠，無法運用" + name() + "。\n");

        msg = HIY "只見$N" HIY "雙目微閉，單手託天。掌心頓時騰起一個無比刺眼的"
              "氣團，正是奧\n義「" NOR + HIW "魔光日無極" NOR + HIY "」。霎時"
              "金光萬道，塵沙四起，空氣熾熱，幾欲沸騰。$N" HIY "\n隨即收攏掌心"
              "，氣團爆裂開來，向四周電射而出，光芒足以和日月爭輝。\n\n" NOR;

        message_combatd(msg, me);

        addn("neili", -1000, me);
        me->start_busy(5);

        ap = attack_power(me, "unarmed") + me->query_con();

        obs = me->query_enemy();
        for (flag = 0, i = 0; i < sizeof(obs); i++)
        {
                dp = defense_power(obs[i], "force") + obs[i]->query_con();

                if (ap * 2 / 3 + random(ap) > dp)
                {
                        switch (random(2))
                        {
                        case 0:
                                tell_object(obs[i], HIR "你只覺眼前金光萬道，周圍空氣幾欲沸"
                                                    "騰，光芒便如利箭一般透體而入。\n" NOR);
                                break;

                        default:
                                tell_object(obs[i], HIR "你只覺眼前金光萬道，周圍空氣幾欲沸"
                                                    "騰，光芒便如千萬細針一齊扎入身體般。\n"
                                                    NOR);
                                break;
                        }

                        damage = attack_power(me, "force");
                        damage+= query("jiali", me);
                        damage *= 2;
                        damage+= random(damage);

                        obs[i]->receive_damage("qi", damage, me);
                        obs[i]->receive_wound("qi", damage, me);

                        obs[i]->receive_damage("jing", damage * 6, me);
                        obs[i]->receive_wound("jing", damage * 3, me);

                        p = (int)query("qi", obs[i]) * 100 / (int)query("max_qi", obs[i]);

                        switch (random(5))
                        {
                        case 0:
                                msg = HIR "只聽" + obs[i]->name() +
                                      HIR "一聲慘嚎，接連退了數步，“"
                                      "哇”的嘔出一大口鮮血。\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;

                        case 1:
                                msg = HIR "只見" + obs[i]->name() +
                                      HIR "向後飛出丈遠，重重的跌落在"
                                      "地上，衣衫燒焦，再也沒力氣站起"
                                      "。\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;

                        case 2:
                                msg = HIR "只見" + obs[i]->name() +
                                      HIR "跌跌撞撞向後連退數步，伏倒"
                                      "在地。鬚眉、衣衫都發出一股焦臭"
                                      "。\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;

                        case 3:
                                msg = HIR "光芒閃過，" + obs[i]->name() +
                                      HIR "卻是呆立當場，動也不動，七"
                                      "竅流血，神情扭曲，煞是恐怖。\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;

                        default:
                                msg = HIR + obs[i]->name() +
                                      HIR "急忙抽身後退，可只見眼前光"
                                      "芒暴漲，一閃而過。全身已多了數"
                                      "個傷口，鮮血飛濺。\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;
                        }
                        if (! obs[i]->is_busy())
                                obs[i]->start_busy(1);
                        message("vision", msg, environment(me), ({ obs[i] }));
                        addn("neili", -500, obs[i]);
                        flag = 1;
                } else
                {
                        tell_object(obs[i], HIY "你只覺眼前金光萬道，周圍空氣幾"
                                            "欲沸騰，大驚之下連忙急運內功，抵禦"
                                            "開來。\n" NOR);
                }
                if (query("neili", obs[i]) < 0)
                        set("neili", 0, obs[i]);
        }

        if (! flag)
                message_combatd(HIY "只見光芒頓斂，卻沒有任何人被$N"
                               HIY "這招擊中。\n\n" NOR, me, 0, obs);

        return 1;
}
