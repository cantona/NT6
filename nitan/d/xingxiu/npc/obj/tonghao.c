// tonghao.c
//

inherit ITEM;

void create()
{
        set_name("銅號", ({ "tonghao" }) );
        set_weight(2000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "這是一把金光閃亮的銅號。\n");
                set("value", 50);
        }
        setup();
}