// miss 追尋物品

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string str)
{
        object ob;

        return notify_fail("該功能已經關閉。\n");
        if( me->is_busy() || query("doing", me) )
                return notify_fail("你的動作還沒有完成，不能追尋物品。\n"); 

        if (me->is_fighting())
                return notify_fail("你正在戰鬥呢，還是安心戰鬥吧。\n"); 

        if (! str)
                return notify_fail("你要追尋什麼物品？\n");

        if( !stringp(str=query("can_summon/"+str, me)) )
                return notify_fail("你不知道如何追尋這個物品。\n");

        if (me->is_ghost())
                return notify_fail("等你還了陽再追尋吧。\n");

        if( query("no_magic", environment(me)) || query("maze", environment(me)) )
                return notify_fail("你在這裡無法感應到你的物品，不可以施法追尋。\n");

        if (! objectp(ob = find_object(str)) || ! environment(ob))
                return notify_fail("你窮盡精力，也無法感應到這個物品。\n");

        ob->receive_miss(me);
        return 1;
}

int help(object me)
{
write(@HELP
指令格式 : miss <煉制物品的ID>

此指令可讓你追尋你煉制的物品，必須有一定的精力才能做到。
HELP
    );
    return 1;
}
