// tongbo.c
//

inherit ITEM;

void create()
{
        set_name("銅鈸", ({ "tongbo" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "對");
                set("long", "這是一對金光閃亮的銅鈸。\n");
                set("value", 50);
        }
        setup();
}