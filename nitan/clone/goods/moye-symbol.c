#include <ansi.h>
inherit ITEM;

int query_autoload() { return 1; }
void create()
{
        set_name(HIM "莫邪聖符" NOR, ({ "moye symbol", "symbol" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "莫邪聖符可以將普通道具升級(into)為下線不掉物品。\n" NOR);
                set("unit", "張");
                set("value", 500000);
        }
        setup();
}

void init()
{
        add_action("do_integrate", "into");
}

int do_integrate(string arg)
{
        object me;
        object ob;

        if (! arg)
                return notify_fail("你要往什麼道具上使用該聖符？\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)) &&
            ! objectp(ob = present(arg, environment(me))))
                return notify_fail("你身上和附近沒有這樣道具啊。\n");
        
        if (ob == this_object() || ob->is_character())
                return notify_fail("你想要幹什麼?\n");
                
        if (ob->query_autoload())
                return notify_fail(ob->name() + "已經是下線不掉物品了，沒有這個必要吧！\n");

        set("set_data", 1, ob);
        set("auto_load", 1, ob);

        tell_object(me, "你把" + name() + "蓋在" + ob->name() + "上，然後口中念念有詞，"
                        "只見聖符化作一道紅光飛入" + ob->name() + "體內！\n");

        tell_object(me, HIC "你感受" + ob->name() + HIC"發生了不可言喻的變化。\n" NOR);

        destruct(this_object());
        return 1;
}