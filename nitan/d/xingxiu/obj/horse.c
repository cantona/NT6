// item: /d/xingxiu/npc/obj/horse.c
// Jay 3/17/96

inherit ITEM;
void setup()
{}

void init()
{
        add_action("do_ride", "ride");
}

void create()
{
        set_name("伊犁馬", ({"horse", "yili ma", "ma"}));
        set_weight(35000);
        set_max_encumbrance(50000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "匹");
                set("long", "一匹良種的伊犁馬，可以騎(ride)，也可以馱東西。\n");
                set("value", 1000);
        }
}

int do_ride(string arg)
{
        object me = this_player();
        if (!id(arg))
                return notify_fail("你要騎什麼？\n");
        if( query_temp("marks/騎", this_player())){
                       write("你已經騎在馬上了。\n");
                        return 1;
        }
        else {
               message("vision",this_player()->name() + "翻身上馬。\n",
                        environment(me), ({me}) );
               write("你戰戰兢兢爬上馬背。還好，別人沒看出來。\n");
                set_temp("marks/騎", 1, this_player());
        return 1;
        }
}