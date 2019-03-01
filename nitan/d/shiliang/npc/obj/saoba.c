// Feb. 6, 1999 by Winder
inherit ITEM;
void create()
{
        set_name( "掃把", ({ "saoba"}));
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long","這是一把用來的打掃衛生的掃把。\n");
             }
}