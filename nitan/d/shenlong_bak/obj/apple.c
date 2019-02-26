// apple.c 蘋果
// by aln 4 / 98

inherit ITEM;
#include <ansi.h>

void create()
{
        set_name("蘋果", ({"ping guo", "apple", "guo"}));
        set_weight(40);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個又大又紅的蘋果\n");
                set("unit", "個");
                set("value", 80);
                set("food_remaining", 5);
                set("food_supply", 5);
        }
}

void init()
{
        add_action("do_yao", "yao");
        add_action("do_yao", "eat");
        add_action("do_yao", "chi");
}

int do_yao(string arg)
{
        if( !this_object()->id(arg) ) 
                return 0;

        if( this_player()->is_busy() )
                return notify_fail("你上一個動作還沒有完成。\n");

        if( !living(this_player()) ) 
                return 0;

        if( !query("food_remaining") )
                return notify_fail( name() + "已經沒什麼好吃的了。\n");

        if( query("food", this_player()) >= this_player()->max_food_capacity() )
                return notify_fail("你已經吃得太多了。\n");

        addn("food", query("food_supply"), this_player());
        this_player()->receive_curing("jing",query("con", this_player()));

        if( this_player()->query_condition("sl_poison") )
        this_player()->apply_condition("sl_poison",
                this_player()->query_condition("sl_poison") - 1);

        if( this_player()->is_fighting() ) this_player()->start_busy(2);

        set("value", 0);
        addn("food_remaining", -1);
        if( !query("food_remaining") ) {
                message_vision("$N將剩下的" + name() + "吃得幹乾淨淨。\n", this_player());
                if( !this_object()->finish_eat() )
                        destruct(this_object());
        } else 
                message_vision("$N拿起" + name() + "咬了幾口。\n", this_player());

        this_player()->start_busy(1);
        return 1;
}

