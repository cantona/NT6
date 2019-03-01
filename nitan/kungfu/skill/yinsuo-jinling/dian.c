// This program is a part of NITAN MudLIB
// dian.c 隔空點穴

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return RED"隔空點穴"NOR; }

int perform(object me, object target)
{
        object weapon;
        object ob;
        int ap, dp;
        string result, str, msg;

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("隔空點穴只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
             || query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對。\n");

        // if (!objectp(obj=present("jinling suo", me)))
        //        return notify_fail("你手中沒有金鈴索，不能使用點穴功夫。\n");

        if( (int)me->query_skill("yinsuo-jinling", 1) < 120 )
                return notify_fail("你的銀索金鈴不夠純熟，還不能認穴\n");

        if( (int)me->query_skill("tianluo-diwang",1)<120)
                return notify_fail("你的天羅地網勢火候不足，手法還不夠靈活\n");

        if( (int)me->query_skill("yunv-xinfa",1)< 135)
                return notify_fail("你的內功修為太差，勁力無法封閉穴道\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("你的內力不足以施展隔空點穴功夫.\n");

        if( query("neili", me)<1000 )
                return notify_fail("你的內力不夠點穴。\n");

        if (me->query_skill_mapped("whip") != "yinsuo-jinling")
                return notify_fail("你沒有激發銀索金鈴，無法施展" +name()+ "！\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "\n$N手上金鈴飛出，使出銀索金鈴的上乘隔空點穴功夫，直取$n的大椎穴。\n\n"NOR;

        ob=query_temp("weapon", target);
        ap=attack_power(me,"whip") + weapon->query_weight();
        dp=defense_power(target,"dodge");

        if (ap / 2 + random(ap) > dp)
        {
                if (! objectp(ob))
                {
                        int damage = 0;

                        if (target->query_skill("dodge") > 200 && random(2) == 0)
                        {
                                switch (random(2))
                                {
                                case 0:
                                        msg += HIR "$n連續變了幾種上乘身法，終于沒能躲過，"
                                                "$N的金鈴正點在$n的檀中穴上，$n只覺得一口"
                                                "涼氣，自丹田而上，心裡有種說不出的難受。\n";
                                        damage = 3;
                                        break;
                                case 1:
                                        msg += HIR "$n輕身飄開，身法靈動之極，眾人正要喝彩，"
                                                      "聽「噗」的一聲，如擊敗革，$n臉色煞白，搖搖欲墜。\n";
                                        damage = 5;
                                        break;
                                }
                        } else
                        if (target->query_skill("force") > 200 && random(2) == 0)
                        {
                                switch(random(2))
                                {
                                case 0:
                                        msg += HIR "$n冷哼一聲，自持內力高強，反手出招，「啵」"
                                                "的一聲輕響，掌鈴相交，$n身行微晃，臉如金紙。\n";
                                        damage = 3;
                                        break;
                                case 1:
                                        msg += HIR "$n一聲長嘯，雙手幻化出無數掌影，護住身前。"
                                                "只聽「嗤」的一聲，掌影頓消，$n已經變得臉色慘白。\n";
                                        damage = 4;
                                        break;
                                }
                        } else
                        {
                                switch(random(2))
                                {
                                case 0:
                                        msg += HIR "$n看到這招，竟然不知躲避，「嗤」的一聲，$N"
                                                "的金鈴正點在$n大椎穴上，$n全身酸軟,跌倒在地。\n";
//                                        target->unconcious();
                                        damage = 5;
                                        break;
                                case 1:
                                        msg += HIR "$n一轉念，已經想出了九十九種化解的辦法，"
                                                "尚未來得及施展，只聽「嗤」的一聲，已被$N點中大椎穴，全身酸軟，跌倒在地。\n";
//                                        target->unconcious();
                                        damage = 5;
                                        break;
                                }
                        }
                        if (damage > 0)
                                target->receive_damage("qi",query("max_qi", target)*damage/15);
                        addn("neili", -(500+damage*40), me);
                        me->start_busy(2);
                        message_combatd(msg + NOR, me, target);
                        str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                        message_combatd("\n($N"+str+")\n", target);
                        return 1;
                }
                if( objectp(ob) && ob->is_item_make() )
                {
                        msg+=HIR"$n忙用"+query("name", ob)+"招架，只覺得虎口劇震，所幸兵器完好無損。\n"NOR;
                } else if (objectp(ob))
                {
                        msg += HIW "$n連忙招架，只聽見「啪」地一聲，$n手中的" + ob->name()+ HIW"竟被彈飛！\n";
                        ob->unequip();
                        ob->move(environment(target));
                }
                target->start_busy(2);
                addn("neili", -200, me);
        } else
        {
                int busy = 0;
                if (target->query_skill("dodge") > 200 && random(2) == 0)
                {
                        switch (random(2))
                        {
                        case 0:
                                msg += "$n一聲輕笑，連續變化了幾次身法，擾人耳目，一時讓$N無法進攻。\n";
                                busy = 2;
                                break;
                        case 1:
                                msg += "$n突然向後飄去，疾若閃電，令$N所有的後繼變化無從施展。\n";
                                busy = 1;
                                break;
                        }
                } else
                if (target->query_skill("force") > 200 && random(2) == 0)
                {
                        switch (random(2))
                        {
                        case 0:
                                msg += "$n臉色凝重，加快格架，以巧對巧，讓$N無從下手，只能收回金鈴。\n";
                                busy = 3;
                                break;
                        case 1:
                                msg += "$n滿臉不屑，冷笑一聲，雙掌齊出，其快無比，令$N只能回招自救。\n";
                                busy = 1;
                                break;
                        }
                } else
                {
                        switch (random(3))
                        {
                        case 0:
                                msg += "$n左搖右晃，看上去毫無章法，偏偏躲過了$N這一擊。\n";
                                busy = 2;
                                break;
                        case 1:
                                msg += "$n金鈴點出，看上去靈動精妙，$N一呆，攻勢頓緩。\n";
                                busy = 2;
                                break;
                        case 2:
                                msg += "$n攝住心神，真氣貫注全身"
                                         + "，堪堪封住了$N的進攻。\n";
                                busy = 2;
                                break;
                        }
                }
                target->start_busy(busy);
        }
        message_combatd(msg + NOR, me, target);
        addn("neili", -500, me);
        me->start_busy(2);
        return 1;
}
