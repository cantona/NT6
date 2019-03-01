// enchase.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string item, tessera;
        object obj, dest;

        if (! arg)
                return notify_fail("你要往什麼道具上鑲嵌物品？\n");

        if (me->is_busy())
                return notify_fail("先忙完了你的事情再做這件事情吧！\n");

        if (me->is_fighting())
                return notify_fail("你現在正在打架，沒時間做這些事情。\n");

        if (sscanf(arg, "%s with %s", item, tessera) != 2 &&
            sscanf(arg, "%s in %s", tessera, item) != 2)
                return notify_fail("你要往這上面鑲嵌什麼物品？\n");

        if (! objectp(obj = present(tessera, me)))
                return notify_fail("你身上沒有這樣東西可以用來鑲嵌。\n");

        if (! objectp(dest = present(item, me)))
                return notify_fail("你身上沒有這樣道具。\n");

        if( query("no_identify", obj) )
                return notify_fail("此物品還沒有簽定。\n");

        if( query("qianghua/level", obj) )
                return notify_fail("此物品已經強化過，無法再鑲嵌物品。\n");

        notify_fail("你無法把" + obj->name() + "鑲嵌到" + dest->name() + "上。\n");

        //return dest->do_enchase(me, obj);
        return ITEM_D->do_enchase(me, dest, obj);

}

int help(object me)
{
        write(@HELP
指令格式 : enchase <特殊物品> in <道具>
           enchase <道具> with <特殊物品>

這個指令可以讓你將某樣特殊物品鑲嵌到另外一種道具上，使得道具
具有特殊的能力。
HELP
        );
        return 1;
}
