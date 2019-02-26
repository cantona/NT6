inherit ITEM;

void create()
{
        set_name("釣魚杆", ({ "fish pole" , "pole", "釣魚杆"}) );
        set_weight(150);
        set_max_encumbrance(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("prep", "on");
                set("long", "一個用桃枝做成的釣魚杆，上面還有含苞待放的桃花，顯得十分新穎別緻。可以用它來釣魚(fishing)。\n");
                set("value", 150);
        }
}

void init()
{
        add_action("do_use", "fishing");
}

int do_use(string arg)
{
//        if( arg != "fish pole" ) return 0;

        tell_object(this_player(),"你掏出一個" + this_object()->name() + "。\n");
        environment(this_player())->fish_notify(this_object(), 0);

        return 1;
}

int is_container() { return 1; }

