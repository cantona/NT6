inherit ITEM;
void setup()
{}

void init()
{
        add_action("do_climb", "zou");
}

void create()
{
        set_name("木板", ({"mu ban", "ban"}));
        set_weight(200000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一塊舊木板，擱在房樑上。\n");
                set("unit", "塊");
                set("material", "wood");
        }
        setup();
}

int do_climb(string arg)
{
        object me = this_player();
        
        if (!id(arg))
                return notify_fail("你要走到哪兒去？\n");
        if( query_temp("marks/跳1", this_player()) )
        {
                write("你怎麼沒完沒了地走？\n");
                return 1;
        }
        else 
        {
                message("vision",this_player()->name() + "小心翼翼地走到木板上,看上去腳有點發軟。\n",
                        environment(me), ({me}) );
                write("你小心翼翼地走到了木板上,心想:還好我沒有恐高症!。\n");
                set_temp("marks/跳1", 1, this_player());
                return 1;
        }
}

