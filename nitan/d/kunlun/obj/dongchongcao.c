// dongchongcao.c 冬蟲草

#include <ansi.h>
inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_fu", "fu");
}

void create()
{
        set_name(HIB"冬蟲草"NOR, ({"dongchong cao", "cao"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "株");
                set("long", HIB"這是一株夏季從冬季鑽入土中的死蟲身上長出的冬蟲夏草。\n"NOR);
                set("value", 2500);
        }
        setup();
}

int do_fu(string arg)
{
        string what = query("cure");
        int howmuch = query("amount");
        object me=this_player();

        if(!id(arg)) return notify_fail("你要吃什麼？\n");
        if(!present(this_object(), me))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎著了。\n");
        if( query("eff_qi", this_player()) == 
                this_player(query("max_qi", )) )
                return notify_fail("你現在身上沒有受到任何傷害！\n");
        else {
                this_player()->receive_curing("qi", 50);
                message_vision("$N把一株冬蟲草放進口中嚼碎，小心敷在傷口上，氣色看起來好多了。\n", this_player());
                destruct(this_object());
                return 1;
        }
}
