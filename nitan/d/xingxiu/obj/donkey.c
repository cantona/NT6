// item: /d/xingxiu/npc/obj/donkey.c
// Jay 3/26/96

inherit ITEM;
void setup()
{}

void init()
{
        add_action("do_ride", "ride");
}

void create()
{
        set_name("小毛驢", ({"mao lv"}));
        set_weight(15000);
        set_max_encumbrance(20000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "匹");
                set("long", "一匹黑色的小毛驢，可以騎，也可以馱東西。\n");
                set("value", 400);
        }
}

int do_ride(string arg)
{
        object me = this_player();
        if (!id(arg))
                return notify_fail("你要騎什麼？\n");
        if( query_temp("marks/騎", this_player())){
                       write("你已經騎在馬上了。還想再騎驢?!\n");
                        return 1;
        }
        else {
               message("vision",this_player()->name() + "翻身上驢。毛驢一撩蹄子，"
                       "又把"+this_player()->name() + "掀下驢背。\n",
                        environment(me), ({me}) );
               write("你想騎毛驢，可它不讓你騎。\n");
        return 1;
        }
}