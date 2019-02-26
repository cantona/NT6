// sheshen.c 捨身技

#include <ansi.h>

inherit F_SSERVER;

string name() { return "捨身"; }

int perform(object me, object target)
{
        mapping skill_status;
        string msg, *sname;
        object weapon;
        int exp, shen, mine, count;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("捨身只能對戰鬥中的對手使用。\n");

        if( me->is_ghost() || query("eff_qi", me)<0 )
                return notify_fail("你已經死了。\n");


        if( me->is_busy() )
                return notify_fail("你現在忙着呢，使不出這一招。\n");


//        if( !me->query("yinliting_teach") )
//                 return notify_fail("你未得教主傳授，不會使用捨身。\n");

        if( (int)me->query_skill("strike") < 250 )
                return notify_fail("你的英雄三招極不夠嫻熟，不會使用捨身。\n");
//        if( me->query("neili") >= 100 || me->query("qi") >= 200)
//                                               return notify_fail("你未到山窮水盡之地，不需用此狠招！\n")
        if( (int)me->query_skill("shenlong-xinfa", 1) < 250 && (int)me->query_skill("busi-shenlong", 1) < 250 )
                return notify_fail("你的內功修為不夠，不會使用捨身。\n");

        if( me->query_skill_mapped("force") != "shenlong-xinfa" &&
            me->query_skill_mapped("force") != "busi-shenlong" )
                return notify_fail("你所用的內功於英雄三招氣路相悖！\n");

        if( query("combat_exp", me)<500000 )
                return notify_fail("你實戰經驗不足，不會使用捨身。\n");

        if( query("shen", target)>10000 )
                shen=-query("shen", me)/50;
        else shen=query("shen", me)/50;

        exp=query("combat_exp", me)/100;

        msg = HIW"$N一聲悲嘯，空門大開，全身撞向$n"+HIW"，已經是拼命的打法！！！\n"NOR;

        mine=random(query("combat_exp", me)-query("shen", me));

        if( mine>query("combat_exp", target)/3*2 )
        {
                msg += HIR"$n"+HIR"猝不及防之下，被$N撲個正着，只覺渾身灼熱無比，卻又渾身動彈不得，\n忍不住了發出一聲聲淒厲的慘叫！！！$n面目變的猙獰可怕，垂死前的掙扎終於停止了。\n兩人都耗盡所有的氣力，只留下驚心動魄的悲慘一幕！！！\n" NOR;
                message_combatd(msg, me, target);
                addn("max_neili", -(30+random(30)), me);
                addn("combat_exp", -exp, me);
                addn("shen", shen, me);
                me->receive_wound("qi",query("max_qi", me)+200, target);
                target->receive_wound("qi",query("max_qi", target)+200, me);
                me->start_busy(3 + random(3));
                if( !target->is_busy() )
                        target->start_busy(3 + random(3));
                set_temp("die_reason", "與"+target->name(1)+"同歸於盡", me);
                set_temp("die_reason", "與"+me->name(1)+"同歸於盡", target);
                me->die();
                target->die();
                return 1;

        }
        else
        {
                msg += HIC "$n" HIC "不料$N" HIC "用此招數，手忙腳亂，狼狽萬狀的躲閃開去，但已嚇得手足冰涼，好一陣動彈不得。\n"NOR;
                message_combatd(msg, me, target);
                me->receive_wound("qi",query("max_qi", me)+200, target);
                me->start_busy(3);
                me->die(target);
                if( !target->is_busy() )
                        target->start_busy(3 + random(3));
                return 1;

        }

        return 1;
}