#include <ansi.h>
inherit ITEM; 

void create()
{
        object good;
        set_name(HIC"寶箱"NOR, ({"box"}) );
        set_weight(300);
        set("no_get", 1);
        set_max_encumbrance(80000000);
        set("unit", "個");
        set("long", "一個散發着神祕光芒的寶箱。\n");
        set("closed", 1);
        set("value", 2000);

        good = new("/clone/money/gold");
        good->set_amount(10+random(10));
        good->move(this_object());
        if (!random(3)) {
                for (int i = 0; i < 7; i++) 
                {
                        good = new("/clone/tessera/rune1" + random(8));
                            good->move(this_object());
                }                  
          }
        setup();
} 
int is_container() {return 1;} 
void init()
{
        add_action("do_open","open");

}
int is_closed()
{
        return (query("closed", this_object()));
} 

int do_open(string arg)
{
        object me, ob;
        me = this_player();
        if(!arg)
                    return 0;
        ob = present(arg,environment(this_object()));
        if (ob!=this_object())
                 return 0;
                                 
        if (!is_closed())
        {
                return notify_fail("寶箱已經打開了。 \n");
        }
        message_vision("$N將寶箱打開。 \n", me);
        set("closed", 0, this_object());
        //me->move(environment(this_object()));
        return 1;
} 
