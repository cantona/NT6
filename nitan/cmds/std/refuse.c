// refuse.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        function f;

        seteuid(getuid());

        if (! arg)
                return notify_fail("你要拒絕誰？\n");

        notify_fail("這人沒有向你提出什麼要求啊？\n");
        if( !functionp(f=query_temp("pending/answer/"+arg+"/refuse", me)) )
                return 0;

        delete_temp("pending/answer/"+arg, me);
        return evaluate(f);
}

int help(object me)
{
   write( @HELP
指令格式: refuse <someone>

拒絕某人向你提出的要求。
HELP );
   return 1;
}
