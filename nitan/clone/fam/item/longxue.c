
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "龍血" NOR, ({ "dragon blood", "dragon", "blood" }) );
        set_weight(30);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "一瓶龍之血液，可以用來修復鑲嵌物(指令 rehab)。\n "
                            HIY "下線丟失    ：   否\n"NOR);
                set("value", 2000000);
                set("unit", "瓶");
        }

        setup();
}

void init()
{
        if (this_player() == environment())
        {
                add_action("do_rehab", "rehab");
        }
}

int do_rehab(string arg)
{
        object me;
        object ob;
        string enid, obid;

        me = this_player();

        if (! arg)return notify_fail("指令格式：rehab <鑲嵌物品ID> in <道具ID>\n");

        if (me->is_busy())
                return notify_fail("先忙完了你的事情再做這件事情吧！\n");

        if (me->is_fighting())
                return notify_fail("你現在正在打架，沒時間做這些事情。\n");

        if (sscanf(arg, "%s in %s", enid, obid) != 2)
                return notify_fail("指令格式：rehab <鑲嵌物品ID> in <道具ID>\n");

        if (! objectp(ob = present(obid, me)))
                return notify_fail("你身上沒有這樣道具。\n");         
        
        if (! ob->query("enchase"))
                return notify_fail(ob->name() + "好像沒有鑲嵌什麼吧！\n" NOR);

        if (! ob->query("enchase/" + enid))
                return notify_fail(ob->name() + "上沒有這個鑲嵌物品。\n" NOR);

        if (ob->query("enchase/" + enid + "/cur_firm") >= 99)
                return notify_fail(ob->query("enchase/" + enid + "/name") + "目前並不需要增加堅固。\n");

        // 開始為鑲嵌物品增加堅固
        ob->set("enchase/" + enid + "/cur_firm", 99);
        ob->save();

        tell_object(me, HIG + ob->query("enchase/" + enid + "/name") + "的堅固增加了！\n" NOR);

        destruct(this_object());

        return 1;
}

int query_autoload()
{
         return 1;
}
