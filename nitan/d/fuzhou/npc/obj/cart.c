// cart.c

inherit ITEM;

void create()
{
        set_name("鏢車", ({ "silver cart", "cart"}) );
        set_weight(3000000);
        set("no_get", 1);
        set_max_encumbrance(80000000);
        set("unit", "輛");
        set("long", "一輛黑漆漆的鏢車，上面插着福威鏢局的大旗。\n");
        set("closed", 1);
        set("value", 2000);
    
}

int is_container() {return 1;}

void init()
{
         add_action("do_open","open");
         add_action("do_close","close");
}

int do_close(string arg)
{
        object me, ob;

        me = this_player();
        ob = this_object();
        if(arg != "cart" && arg != "silver cart")
                return notify_fail("你要關上什麼？\n");
               message_vision("$N把$n門關上了。\n", me, ob);
        set("closed", 1, ob);
        return 1;
}

int do_open(string arg)
{
        object me, ob;

        if(arg != "cart" && arg != "silver cart")
                return notify_fail("你要打開什麼？\n");
        me = this_player();
        if (objectp(ob=present("biao tou",environment())))
                return notify_fail(ob->name()+"瞪了你一眼：“你要幹什麼！”\n");
        set("closed", 0, this_object());
        message_vision("$N將$n蓋打開。\n", me, this_object());
        return 1;
}

int is_closed()
{
        return (query("closed", this_object()));
}