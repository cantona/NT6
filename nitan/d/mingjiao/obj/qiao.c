// Code of ShenZhou
inherit ITEM;


void create()
{
        set_name("鐵鍬", ({ "tie qiao", "qiao" }) );
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一把普普通通的鐵鍬，看起來毫不起眼。\n"
);
                set("unit", "把");
                set("no_get", 1);
                set("no_drop", 1);


        }

}