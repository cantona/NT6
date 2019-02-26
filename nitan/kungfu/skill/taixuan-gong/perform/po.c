// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;

#define PO "「" HIC "乘風破浪" NOR "」"

int perform(object me)
{
        object *obs;
        string msg;
        int damage;
        int ap, dp;
        int flag;
        int i;
        int p;

        if( userp(me) && !query("can_perform/taixuan-gong/po", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        me->clean_up_enemy();

        if (! me->is_fighting())
                return notify_fail(PO "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(PO "只能空手施展。\n");
                
        if( query("max_neili", me)<8500 )
                return notify_fail("你的內力的修為不夠，現在無法使用" PO "。\n");

        if (me->query_skill("taixuan-gong", 1) < 260)
                return notify_fail("你的太玄功還不夠嫻熟，難以施展" PO "。\n");

        if (me->query_skill_mapped("force") != "taixuan-gong")
                return notify_fail("你現在沒有激發太玄功為內功，難以施展" PO "。\n");

        if (me->query_skill_prepared("unarmed") != "taixuan-gong")
                return notify_fail("你現在沒有準備使用太玄功，難以施展" PO "。\n");

        obs = me->query_enemy();

        if( query("neili", me)<sizeof(obs)*220 )
                return notify_fail("你的真氣不夠，無法運用" PO "。\n");

        msg = HIW "只見$N" HIW"仰望天際，心中思緒萬千。忽然間，$N" HIW "一聲長歎，"
              "隨即雙掌不停地拍出，俠客島石壁上的太玄圖譜已一幅幅湧上心頭，"
              "霎那間四周狂風驟起，塵土飛揚，氣勢如虹。這正是太玄功絕招「" 
              NOR + HIC "乘風破浪" NOR + HIW "」。轉眼間，$N" HIW "雙掌越發"
              "凌厲，已不知不覺地將四周籠罩，當真令人膽戰心驚。\n" NOR;

        message_combatd(sort_msg(msg), me);

        me->start_busy(5);

        ap=attack_power(me,"force")+query("con", me)*10;
  
        addn("neili", -(sizeof(obs)*220), me);

        for (flag = 0, i = 0; i < sizeof(obs); i++)
        {
                dp=defense_power(obs[i],"force")+query("con", obs[i])*10;

                if (ap * 11 / 20 + random(ap) > dp)
                {
                        switch (random(2))
                        {
                        case 0:
                                tell_object(obs[i], HIR "你只覺眼前風沙飛揚，周圍風聲蕭蕭，"
                                                    "一股內勁已經穿體而過。\n" NOR);
                                break;

                        default:
                                tell_object(obs[i], HIR "你只覺眼前風沙飛揚，周圍風沙狂舞，"
                                                    "猛然間只覺千萬股內勁已穿體而過。\n" NOR);
                                break;
                        }

                        damage = damage_power(me, "force");

                        obs[i]->receive_damage("qi", damage, me);
                        obs[i]->receive_wound("qi", damage * 2 / 3 , me);

                        obs[i]->receive_damage("jing", damage / 4, me);
                        obs[i]->receive_wound("jing", damage / 6, me);

                        p=query("qi", obs[i])*100/query("max_qi", obs[i]);

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
                                      "地上，衣衫破爛，再也無法站起來"
                                      "。\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;

                        case 2:
                                msg = HIR "只見" + obs[i]->name() +
                                      HIR "歪歪斜斜倒退幾步，伏倒"
                                      "在地，痛苦不堪。"
                                      "。\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;

                        case 3:
                                msg = HIR "狂風捲過，" + obs[i]->name() +
                                      HIR "只見，飛沙狂舞，卻動也動不了"
                                      "忽然間，卻癱軟在地。\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;

                        default:
                                msg = HIR + obs[i]->name() +
                                      HIR "急忙飛身而起，卻猛然墜地，傷痕遍體，鮮"
                                      "血不止。\n" NOR;
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
                        tell_object(obs[i], HIY "你只覺風沙狂起，頓時運力抵抗，方才擋"
                                    "住這招。\n" NOR);
                }
                if( query("neili", obs[i])<0 )
                        set("neili", 0, obs[i]);
        }

        if (! flag) 
                message_combatd(HIY "風沙驟停，卻沒有任何人受傷。\n\n" NOR, me, 0, obs);

        return 1;
}
