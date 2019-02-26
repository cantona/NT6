#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object ob;

        if (! arg)
                return notify_fail("你要溶化什麼道具的凹槽物品？\n");

        if (me->is_busy())
                return notify_fail("先忙完了你的事情再做這件事情吧！\n");

        if (me->is_fighting())
                return notify_fail("你現在正在打架，沒時間做這些事情。\n");

        if (! objectp(ob = present(arg, me)))
                return notify_fail("你身上沒有這樣道具。\n");

        if( query("equipped", ob) )
                return notify_fail("你先解除" + ob->name() + CYN "的裝備再説！\n");

        if( !ob->is_item_make() && !query("unique", ob) )
                return notify_fail("這類物品無須清理凹槽。\n");

        if( !wizardp(me) && (ob->is_item_make() && ob->item_owner() != query("id", me)) )
                return notify_fail("這不是你的物品。\n");

        if( !query("armor_type", ob) && !query("skill_type", ob) )
                return notify_fail("這類物品無須清理凹槽。\n");

        if( !query("enchase/flute", ob) )
                return notify_fail("這還沒有開槽過了呢。\n");

        if( !query("enchase/used", ob) )
                return notify_fail("這上面沒有鑲嵌過東西。\n");

        notify_fail(ob->name() + "的凹槽物品沒有辦法被熔鍊。\n");

        return ob->do_wash(me);
}

int help(object me)
{
write(@HELP
指令格式 : melt <物品名稱>

這個指令可以讓你運用內力將道具凹槽裏的物品溶化掉。
HELP
    );
    return 1;
}
