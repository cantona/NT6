// This program is a part of NITAN MudLIB
// dian.c 指點江山

#include <ansi.h>

inherit F_SSERVER;
string name() { return "指點江山"; }

int perform(object me, object target)
{
        object weapon;
        object ob;              // 對手的武器
        string msg;
        int ap, dp;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("絕技「指點江山」只能對戰鬥中的對手使用。\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                        return notify_fail("你不能使用武器！\n");


        if( (int)me->query_skill("yizhi-chan", 1) < 150 )
                return notify_fail("你的一指禪太生疏，不會使用「指點江山」。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的內力不夠，現在無法使用「指點江山」。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        addn("neili", -100, me);

        msg = HIY " $N深深吸了一口氣，伸出中指，使出佛門伏魔無上絕技指法，慢慢得向$n點了過去。\n";

        ob=query_temp("weapon", target);
        ap = attack_power(me, "finger");
        dp = defense_power(target, "force");

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
                                        msg += HIR " $n連續變了幾種上乘身法，終于沒能躲過，"
                                                "$N的這一指正點在$n的丹田上，\n$n只覺得一口"
                                                "涼氣，自丹田而上，心裡有種說不出的難受。\n";
                                        damage = 3;
                                        break;
                                case 1:
                                        msg += HIR " $n輕身飄開，身法靈動之極，眾人正要喝彩，"
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
                                        msg += HIR " $n冷哼一聲，自持內力高強，反手出招，「啵」"
                                                "的一聲二指相交，$n身行微晃，臉如金紙。\n";
                                        damage = 3;
                                        break;
                                case 1:
                                        msg += HIR " $n一聲長嘯，雙手幻化出無數掌影，護住身前。"
                                                "只聽「嗤」的一聲，掌影頓消，$n已經變得臉色慘白。\n";
                                        damage = 4;
                                        break;
                                }
                        } else
                        {
                                switch(random(2))
                                {
                                case 0:
                                        msg += HIR " $n看到這招，竟然不知躲避，「嗤」的一聲，$N"
                                                "這一指正點在$n的檀中大穴。\n";
                                        damage = 0;
                                        break;
                                case 1:
                                        msg += HIR " $n一轉念，已經想出了九十九種化解的辦法，"
                                                "尚未來得及施展，只聽「嗤」的一聲，已被$N點中檀"
                                                "中大穴。\n";
                                        damage = 0;
                                        break;
                                }
                        }
                        message_combatd(msg + NOR, me, target);
                        if (damage > 0)
                        {
                                target->receive_damage("qi",query("max_qi", target)*damage/12,me);
                                COMBAT_D->report_status(target);
                        }
                        else
                                target->unconcious(me);

                        me->start_busy(2);
                        return 1;
                }
                if (ob->is_item_make())
                {
                        ob->move(environment(target));
                        set("consistence", 0, ob);
                        msg+=HIR"$n忙用"+query("name", ob)+"招架，只覺得虎口劇震，兵器脫手而出！。\n"NOR;
                } else
                {
                        msg += HIW " $n連忙招架，只聽見「啪」地一聲，$n手中的" + ob->name()
                                + "寸寸斷裂，散落一地！\n";
                        ob->unequip();
                        ob->move(environment(target));
                        set("name", "斷掉的"+query("name", ob), ob);
                        set("value", 0, ob);
                        set("weapon_prop", 0, ob);
                }
                me->start_busy(2);
                if (! target->is_busy()) target->start_busy(ap/120 + 2);
        } else
        {
                int busy = 0;
                if (target->query_skill("dodge") > 200 && random(2) == 0)
                {
                        switch (random(2))
                        {
                        case 0:
                                msg += " $n一聲輕笑，連續變化了幾次身法，擾人耳目，一時讓$N無法進攻。\n";
                                busy = 2;
                                break;
                        case 1:
                                msg += " $n突然向後飄去，疾若閃電，令$N這一指所有的後繼變化無從施展。\n";
                                busy = 1;
                                break;
                        }
                } else
                if (target->query_skill("force") > 200 && random(2) == 0)
                {
                        switch (random(2))
                        {
                        case 0:
                                msg += " $n臉色凝重，緩緩出掌，以拙對拙，竟然讓$N無從下手，只得收指。\n";
                                busy = 3;
                                break;
                        case 1:
                                msg += " $n滿臉不屑，冷笑一聲，雙掌齊出，其快無比，令$N只能回招自救。\n";
                                busy = 1;
                                break;
                        }
                } else
                {
                        switch (random(3))
                        {
                        case 0:
                                msg += " $n左搖右晃，看上去毫無章法，偏偏躲過了$N這一擊。\n";
                                busy = 2;
                                break;
                        case 1:
                                msg += " $n一指點出，看上去恍若也是佛門精妙指法，$N一呆，攻勢頓緩。\n";
                                busy = 2;
                                break;
                        case 2:
                                if (objectp(ob))
                                msg+="$n攝住心神，真氣貫注"+query("name", ob )
                                         + "，堪堪封住了$N的進攻。\n";
                                else
                                msg += "$n攝住心神，真氣貫注雙掌，堪堪封住了$N的進攻。\n";
                                busy = 2;
                                break;
                        }
                }
                if (! target->is_busy())
                        target->start_busy(busy);
                me->start_busy(3);
        }
        message_combatd(msg + NOR, me, target);

        return 1;
}