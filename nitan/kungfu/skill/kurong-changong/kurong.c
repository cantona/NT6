// Code of ShenZhou
// kurong.c 枯榮心法
// Modify By Scatter

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("枯榮心法對他人毫無作用！\n");

        if( query_temp("kurong", me) )
                return notify_fail("你已在運轉枯榮心法了。\n");

        if (me->query_skill("kurong-changong",1) < 100
                || me->query_skill("force",1) < 100
                || me->query_skill("buddhism",1) < 100 )
                return notify_fail("你的尚未參通枯榮禪，強運枯榮心法毫無益處！\n");

        if( query("max_neili", me)<2000
                 || query("neili", me)<query("max_neili", me)/10 )
                return notify_fail("你的內力不夠運轉枯榮心法！\n");

        skill=me->query_skill("kurong-changong",1)+me->query_skill("buddhism",1);

        message("vision",HIW"\n"+query("name", me)+"雙掌合十，氣息流轉下，一張臉片刻間變得血肉全無只剩枯骨！再片刻，又回復血肉充盈的模樣。\n\n"NOR,environment(me),me);
        tell_object(me, HIW "\n你雙掌合十，運轉枯榮心法，一股真氣自丹田而生，沿心脈流轉不息，臉上一枯一榮閃現，片刻即回復正常。\n\n" NOR);

        set_temp("kurong", skill*4*query("max_neili", me)/2000, me);

        call_out("checking", 1, me);
        addn("neili", -query("max_neili", me)/10, me);

        return 1;
}

void checking(object me)
{
        int maxqi, amount;

        if (!me) return;

        if (!living(me))
        {
                delete_temp("kurong", me);
                return;
        }

        if( !query_temp("kurong", me)){
                tell_object(me, HIW "你感到丹田真氣混濁，運轉的枯榮心法漸漸散去。\n" NOR);
                return;
        }

        if (me->query_skill_mapped("force") != "kurong-changong")
        {
                delete_temp("kurong", me);
                return;
        }

        if (!me->is_fighting()) {
                if( query_temp("kurong", me) <= 50 )
                        delete_temp("kurong", me);
                else addn_temp("kurong", -50, me);
        }

        maxqi=query("eff_qi", me);

        if (me->is_ghost()) {
                delete_temp("kurong", me);
                return;
        }

        if( living(me) && (maxqi<query("max_qi", me)*95/100 && query("neili", me)>150)){
                amount=(me->query_skill("kurong-changong",1)+me->query_skill("buddhism",1))/4+query("con", me);
                addn("neili", -100, me);
                me->receive_curing("qi", amount);
                message_vision("$N深深吸了幾口氣，氣息流轉下傷口的血流自動止住了。\n", me);
        }

        if( living(me) && (query("qi", me)<(maxqi*2/3))){
                amount=maxqi-query("qi", me);
                if( amount>query_temp("kurong", me))amount=query_temp("kurong", me);
                addn_temp("kurong", -amount, me);
                me->receive_heal("qi", amount);
                message_vision("$N深深吸了幾口氣，臉色看起來好多了。\n", me);
        }

        call_out("checking", 2, me);
        return;
}