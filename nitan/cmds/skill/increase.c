// increase.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object obj, item;

        if (! arg)
                return notify_fail("你要改造什麼物品？\n");

        if (me->is_busy())
                return notify_fail("先忙完了你的事情再做這件事情吧！\n");

        if (me->is_fighting())
                return notify_fail("你現在正在打架，沒時間做這些事情。\n");

        if (! objectp(item = present(arg, me)))
                return notify_fail("你身上沒有這樣道具。\n");

        if (! objectp(obj = present("increase stone", me)))
                return notify_fail("你身上沒有改造石。\n");

        notify_fail(item->name() + "沒有辦法被改造。\n");

        return item->do_increase(me, obj);
}

int help(object me)
{
write(@HELP
指令格式 : increase <物品名稱>

這個指令可以讓你改造道具，以鍛鍊那種道具或是發揮它的威力，每
次消耗改造石一塊。

HELP
    );
    return 1;
}