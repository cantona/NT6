// berserk.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        int max;
        int pts;

        if ((max = me->query_max_craze()) < 1)
                return notify_fail("你的性格不合，不善發作。\n");

        if (me->query_con() < 35 && me->query_str() < 35)
                return notify_fail("你的身體素質還不夠好，貿然發作有傷身體。\n");

        if (me->is_busy())
                return notify_fail("你現在忙著呢。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你的內力不夠充沛，難以控制自己的情緒。\n");

        message_vision(HIR "$N" HIR "嘿然冷笑，關節喀啦喀啦"
                       "的響個不停，一股悍氣油然而起。\n" NOR, me);

        pts = max * random(me->query_skill("force") + 500) / 1000;
        me->improve_craze(pts);
        pts = pts * 10 / me->query_con();
        me->receive_damage("qi", pts);
        addn("neili", -200-random(200), me);
        me->start_busy(1);

        return 1;
}

int help (object me)
{
        write(@HELP
指令格式: berserk|baofa
 
這個指令讓你運用內功控制情緒，大行發作，積蓄自己的憤怒。不過
生氣對自己沒有好處，每次發作都會讓自己的氣受到損失。在身體不
支的時候發怒小心暈厥。

HELP );
        return 1;
}