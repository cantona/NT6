// Feb. 6, 1999 by Winder
inherit ITEM;
void create()
{
        set_name( "手帕", ({ "wen shoupa"}));
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long","這是一張繡花手帕。\n");
             }
}