// dart_limit.c 
#include <ansi.h>
#include <condition.h>
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        if (duration < 1) return 0;
        me->apply_condition("guojob2_busy", duration - 1);

        if (duration == 1)
        {
                me->apply_condition("guojob2_busy", 0);     
                message_vision(CYN "\n一名宋兵跑過來對$N説道：蒙古靼子又開始進攻了，元帥叫你立刻前去待命！\n" NOR, me);
        }

        return CND_CONTINUE;      
}
