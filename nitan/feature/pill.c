// pill.c

#include <name.h>

void init()
{
        add_action("do_eat", "eat");
}

int do_eat(string arg)
{
        string healwhat;

        if( !this_object()->id(arg) ) return 0;
        if( this_player()->is_busy() )
                return notify_fail("你正忙着呢。\n");

        if (!(healwhat = query("heal")))
                return notify_fail("這樣東西不能療傷。\n");


        if( !query("food_remaining") )
                return notify_fail( name() + "已經沒什麼好吃的了。\n");
        if( (int)query("food", this_player()) >= (int)this_player()->max_food_capacity() )
                return notify_fail("你已經吃太飽了，再也塞不下任何東西了。\n");

        addn("food", query("food_supply"), this_player());
        if( this_player()->is_fighting() ) this_player()->start_busy(2);

        // This allows customization of drinking effect.
        if( query("eat_func") ) return 1;

        set("value", 0);
        addn("food_remaining", -1);
        if( !query("food_remaining") ) {
                message_vision("$N將剩下的" + name() + "吃得乾乾淨淨。\n", this_player());
                if( !this_object()->finish_eat() )
                        destruct(this_object());
        } else
                message_vision("$N拿起" + name() + "咬了幾口。\n", this_player());

        return 1;
}
