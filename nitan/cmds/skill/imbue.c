// imbue.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string item, imbue;
        object obj, dest;

        if (! arg)
                return notify_fail("你要往什麼道具上浸入其他物品？\n");

        if (me->is_busy())
                return notify_fail("先忙完了你的事情再做這件事情吧！\n");

        if (me->is_fighting())
                return notify_fail("你現在正在打架，沒時間做這些事情。\n");

        if (sscanf(arg, "%s with %s", item, imbue) != 2 &&
            sscanf(arg, "%s in %s", imbue, item) != 2)
                return notify_fail("你要往這上面浸入什麼物品？\n");

        if (! objectp(obj = present(imbue, me)))
                return notify_fail("你身上沒有這樣東西可以用來浸入。\n");

        if (! objectp(dest = present(item, me)))
                return notify_fail("你身上沒有這樣道具。\n");

        notify_fail("你無法把" + obj->name() + "浸入" +
                    dest->name() + "。\n");
        return dest->do_imbue(me, obj);
}

int help(object me)
{
write(@HELP
指令格式 : imbue <特殊物品> in <道具>
           imbue <道具> with <特殊物品>

這個指令可以讓你將某樣特殊物品浸入另外一種道具中，以鍛煉那種
道具或是發揮它的威力。
HELP
    );
    return 1;
}