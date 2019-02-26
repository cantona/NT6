// inspire.c

#include <ansi.h>

int exert(object me, object target)
{
        string force;

        if( !query("breakup", me) )
                return notify_fail("你還沒有領悟利用真氣激勵精神的訣竅。\n");

        if (me->is_fighting())
                return notify_fail("現在你正在戰鬥中？還是等打完了再説吧！\n");

        force = me->query_skill_mapped("force");
        if (! stringp(force))
                return notify_fail("先激發你的特殊內功。\n");

        if ((int)me->query_skill(force, 1) < 200)
                return notify_fail("你的" + to_chinese(force) + "修為還不夠。\n");

        if( query("eff_jing", me) >= query("max_jing", me) )
                return notify_fail("你現在精神飽滿，有什麼好激勵的？\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠。\n");

        if( query("eff_jing", me)<query("max_jing", me)/3 )
                return notify_fail("你的精損傷太重，現在難以振奮自己。\n");

        message_vision(HIW "$N" HIW "盤膝坐下，閉目冥神，緩緩的呼吸吐納。\n" NOR, me);
        set_temp("pending/inspiring", 1, me);
        me->set_short_desc("正坐在地下運功療傷。");
        me->start_busy((:call_other, __FILE__, "inspiring" :),
                       (:call_other, __FILE__, "halt_inspiring" :));
        return 1;
}

// 振奮中
int inspiring(object me)
{
        string force;
        int recover_points;

        force = me->query_skill_mapped("force");
        if (! stringp(force))
        {
                // 沒有特殊內功了？
                tell_object(me, "你一時難以定奪如何運用內力，只好先暫停療傷。\n");
                set_temp("pending/inspiring", 0, me);
                me->set_short_desc(0);
                message_vision("$N歎了口氣，搖搖晃晃的站了起來。\n", me);
                return 0;
        }

        if( query("eff_jing", me)<query("max_jing", me) )
        {
                // 需要繼續療傷
                if( query("neili", me)<100 )
                {
                        tell_object(me, "你覺得真氣不濟，難以在經脈中繼續運轉振奮。\n");
                        set_temp("pending/healing", 0, me);
                        me->set_short_desc(0);
                        message_vision("$N歎了口氣，搖搖晃晃的站了起來。\n", me);
                        return 0;
                }

                recover_points = 5 + (int)me->query_skill("force") / 6;
                me->receive_curing("jing", recover_points);
                addn("neili", -100, me);
                switch (random(10))
                {
                case 0:
                        tell_object(me, "你運用" + to_chinese(force) + "沿着"
                                    "諸大穴慢慢運轉，振奮精神。\n");
                        break;
                case 1:
                        tell_object(me, "你將內力納入丹田，再上行衝頂，透泥宮"
                                    "，頓覺精神爽快。\n");
                        break;
                case 2:
                        tell_object(me, "你運轉內力，緩緩呼吸吐納，額頭上滲出"
                                        "點點汗珠，隨即化作白霧蒸騰而起。\n");
                        break;
                }

                return 1;
        }

        // 恢復完畢
        set_temp("pending/exercise", 0, me);
        me->set_short_desc(0);
        message_vision(HIY "$N" HIY "緩緩睜開雙目，精光四射，神清意爽。\n" NOR,
                       me);
        return 0;
}

// 停止療傷
int halt_inspiring(object me)
{
        tell_object(me, "你將真氣收回丹田，微微喘息，站了起來。\n");
        tell_room(environment(me), me->name() + "猛的吸一口氣，突然站了起來。\n", me);
        set_temp("pending/inspiring", 0, me);
        me->set_short_desc(0);
        return 1;
}
