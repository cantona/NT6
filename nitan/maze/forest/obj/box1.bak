#include <ansi.h>
inherit ITEM; 

string *ob_list = ({
        "/clone/fam/skpaper/blade1",
        "/clone/fam/skpaper/claw1",
        "/clone/fam/skpaper/club1",
        "/clone/fam/skpaper/cuff1",
        "/clone/fam/skpaper/dagger1",
        "/clone/fam/skpaper/finger1",
        "/clone/fam/skpaper/hammer1",
        "/clone/fam/skpaper/hand1",
        "/clone/fam/skpaper/parry1",
        "/clone/fam/skpaper/staff1",
        "/clone/fam/skpaper/strike1",
        "/clone/fam/skpaper/sword1",
        "/clone/fam/skpaper/throwing1",
        "/clone/fam/skpaper/unarmed1",
        "/clone/fam/skpaper/whip1",
});
void create()
{
        object good;
        set_name(HIC"寶箱"NOR, ({"box"}) );
        set_weight(300);
        set("no_get", 1);
 
        set_max_encumbrance(80000000);
        set("unit", "個");
        set("long", "一個散發著神秘光芒的寶箱。\n");
        set("closed", 1);
        set("value", 2000);
 
/*
        good = new("/clone/money/gold");
        good->set_amount(5+random(5));
        good->move(this_object());
*/
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
        object me, ob, obj;
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
        if( random(10) < 7 )
        {
                obj = new("/clone/money/silver");
                obj->move(this_object());
        }
        else
        {
                obj = new(ob_list[random(sizeof(ob_list))]);
                obj->move(this_object());
        }
        return 1;
} 