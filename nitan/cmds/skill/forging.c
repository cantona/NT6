// forging.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object obj, item;

        if (! arg)
                return notify_fail("你要鍛造什麼物品？\n");

        if (me->is_busy())
                return notify_fail("先忙完了你的事情再做這件事情吧！\n");

        if (me->is_fighting())
                return notify_fail("你現在正在打架，沒時間做這些事情。\n");

        if (! objectp(item = present(arg, me)))
                return notify_fail("你身上沒有這樣道具。\n");

        if (! item->is_item_make()) 
                return notify_fail("你只能鍛造自造兵器或防具！\n"); 

        if (! stringp(item->item_owner()) ||
              item->item_owner() != query("id", me) )
                return notify_fail("你只能鍛造自己的兵器或防具！\n");

        if( query("equipped", item) )
                return notify_fail("你先解除" + item->name() + "的裝備再説！\n"); 
                
        if (! objectp(obj = present("forging stone", me)))
                return notify_fail("你身上沒有鍛造石，鍛造道具需要一塊鍛造石。\n");

        notify_fail(item->name() + "沒有辦法被鍛造。\n");

        return item->do_forging(me, obj);
}

int help(object me)
{
        write(@HELP
指令格式 : forging <道具>

這個指令可以讓你鍛造道具，以鍛鍊那種道具的等級，每次消耗
鍛造石一塊。

HELP
        );
        return 1;
}
