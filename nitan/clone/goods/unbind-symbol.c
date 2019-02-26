#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(YEL "解除綁定符" NOR, ({ "unbind symbol", "unbind", "symbol" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", YEL "該符文可以解除(unbind)物品的綁定屬性。\n" NOR);
                set("unit", "塊");
                set("value", 500000);
        }
        setup();
}

void init()
{
        add_action("do_unbind", "unbind");
}

int do_unbind(string arg)
{
        object me;
        object ob;

        if (! arg || arg == "")
                return notify_fail("你要往什麼道具上使用該神符？\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)) &&
            ! objectp(ob = present(arg, environment(me))))
                return notify_fail("你身上和附近沒有這樣道具啊。\n");

        if (ob == this_object() || ob->is_character())
                return notify_fail("你想要幹什麼?\n");

        if (!query("bindable", ob))
                return notify_fail("這個物品沒有綁定過，無需解除綁定！\n");

        delete("bindable", ob);
        delete("bind_owner", ob);
        set("set_data", 1, ob);
        set("auto_load", 1, ob);

        tell_object(me, "你把" + name() + "蓋在" + ob->name() + "上，然後口中唸唸有詞，"
                        "只見聖符化作一道紅光飛入" + ob->name() + "體內！\n");

        tell_object(me, HIC "你感受" + ob->name() + HIC"已經解除了綁定。\n" NOR);

        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}


