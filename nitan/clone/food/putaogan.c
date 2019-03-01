// 神話世界﹒西遊記﹒版本４．５０
/* <SecCrypt CPL V3R05> */
 
inherit ITEM;
void init();
void eat();

void create()
{
        set_name("葡萄幹", ({"putao gan", "gan"}));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "葡萄幹是西北邊疆的特產，吃起來香甜可口．\n");
                set("unit", "把");
                set("value", 60);
                set("food_remaining", 4);
                set("food_supply", 10);
        }
}
void init()
{
        add_action("do_chi", "eat");
}


int do_chi(string arg)
{
        if( !this_object()->id(arg) ) 
     return 0;

        if( this_player()->is_busy() )
            return notify_fail("你上一個動作還沒有完成。\n");

        if(!arg) 
     return notify_fail("你要吃什麼？\n");
           
        if( query("food", this_player()) >= this_player()->max_food_capacity() )
                return notify_fail("你已經吃太飽了，再也塞不下任何東西了。\n");

        message_vision("$N從兜裡掏出把葡萄幹，一顆一顆的塞到嘴裡，\n一顆，一顆，又一顆．．．\n" , this_player());
   addn("food", 30, this_player());
   destruct(this_object());
        return 1;
}

 
