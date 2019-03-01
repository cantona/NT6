#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("錦盒", ({ "jin he", "he" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "這是裝舍利子的盒子,你似乎應該交還失主。\n");
                set("value", 1000);
                set("no_sell", 1);
                set("material", "wood");
        }
        setup();
}

void init()
{
        add_action("do_open", "open");
}

int do_open(string arg)
{
        object me, ob;
        
        me = this_player();

        if(!arg&&arg!="he") return notify_fail("你要打開什麼東西？\n");
        message_vision("$N打開盒子，只見兩支毒箭飛射而出，擦身而過！\n",me);
        message_vision("一個黑影突然出現，從$N手中一把搶過錦盒，飛身而去！\n",me);
        destruct(this_object());
        return 1;
}