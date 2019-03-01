// by Lonely

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{   
        if (duration == 1)
        {
                tell_object(me, HIR "你一個月沒有繼續化毒，體內毒力已經開始漸漸不受控制！\n" NOR );
                message("vision", me->name() +"的身體一震，神色發散，臉色開始發青。\n", environment(me), me);
                me->apply_condition("hua_poison", 80 + me->query_skill("huagong-dafa", 1));
        }
        me->apply_condition("hua_du", duration - 1);

        if (duration < 1) return 0;
        return CND_CONTINUE;
}
