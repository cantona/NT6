inherit ITEM;

#include <ansi.h>

void init()
{
        add_action("do_drink", "drink");
}

void create()
{
        set_name(HIC "冬瓜湯" NOR, ({"tang"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "碗");
                set("long", "這是一碗味道鮮美的冬瓜湯。\n");
                set("value", 0);
                set("drink_remaining", 5);
                set("drink_supply", 30);
        }
        setup();
}

int do_drink(string arg)
{
        if ( !this_object()->id(arg) ) return 0;

        if ( this_player()->is_busy() )
                return notify_fail("你上一個動作還沒有完成。\n");

        if( query("water", this_player()) >= this_player()->max_water_capacity() )
                return notify_fail("你已經喝太多了，再也灌不下一滴水了。\n");

        addn("water", query("drink_supply"), this_player());

        if ( this_player()->is_fighting() ) 
                this_player()->start_busy(2);

        addn("drink_remaining", -1);

        if ( query("drink_remaining") )
        {
                   message_vision("$N捧起湯碗，美美的喝了一口鮮湯。\n", this_player());
        }
        else 
        { 
                   message_vision("$N捧起湯碗，喝幹了最後一滴鮮湯。\n", this_player());
                destruct(this_object());
        }

        return 1;
}