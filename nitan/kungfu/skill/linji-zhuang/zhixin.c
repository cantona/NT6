// zhixin.c

#include <ansi.h>

int exert(object me, object target)
{
        int level = me->query_skill("linji-zhuang", 1);

        if (level < 60) return notify_fail("你的臨濟十二莊修為還不夠。\n");

        if( query("max_neili", me)<5*level )
                return notify_fail("你的內力還不夠強。\n");

        if( query("neili", me)<4*level )
                return notify_fail("你的真氣不夠。\n");

        if( query("eff_qi", me)<query("max_qi", me)/2 )
                return notify_fail("你已經受傷過重，只怕一運真氣便有生命危險！\n");

        if( query_temp("linji/zhixin", me) )
                return notify_fail("你已經運用之心二莊凝聚心神了。\n");

        set_temp("linji/zhixin", 1, me);
        write( HIY "你微一凝神，運動之心兩莊，去濁氣出體外，收清氣入心中，只覺靈台清明，領悟力似乎有所增加。\n" NOR);
        message("vision",
                HIY + "只見" + me->name() + "微一凝神，吞吐幾口長氣，一對眼眸靈動晶亮，神採弈弈。\n" NOR,
                environment(me), me);

        addn("neili", -4*level, me);
        level += me->query_skill("literate", 1);
        level = 1+random(level)/16;
        addn_temp("apply/int", level, me);
        set("jiali", 0, me);

        me->start_call_out( (: call_other, __FILE__, "recover", me, level :), 1800);

        return 1;
}

void recover(object me, int level)
{
        addn_temp("apply/int", -level, me);
        delete_temp("linji/zhixin", me);

        tell_object(me, HIG"你體內已積過多濁氣，似乎領悟力又歸于尋常。\n"NOR);
}