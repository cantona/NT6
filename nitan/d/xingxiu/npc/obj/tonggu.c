// tonggu.c
//

inherit ITEM;

void create()
{
        set_name("銅鼓", ({ "tonggu" }) );
        set_weight(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("long", "這是一隻金光閃亮的銅鼓。\n");
                set("value", 70);
        }
        setup();
}