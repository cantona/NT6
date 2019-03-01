// tiexiang.c

inherit ITEM;
void setup()
{}

void init()
{
        add_action("do_climb", "climb");
}

void create()
{
        set_name("鐵箱", ({"tie xiang", "xiang", "box"}));
        set_weight(200000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一隻有大又笨的鐵箱子，有些生鏽了。\n");
                set("unit", "只");
                set("material", "steal");
        }
        setup();
}

int do_climb(string arg)
{
        object me = this_player();
        if (!id(arg))
                return notify_fail("你要往哪兒爬？\n");
        if( query_temp("marks/跳1", this_player())){
                       write("你怎麼爬個沒完沒了？\n");
                        return 1;
        }
        else {
               message("vision",this_player()->name() + "爬上箱子。\n",
                        environment(me), ({me}) );
               write("你爬上箱子。\n");
                set_temp("marks/跳1", 1, this_player());
        return 1;
        }
}
