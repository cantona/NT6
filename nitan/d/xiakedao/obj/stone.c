// stone.c
inherit ITEM;

void create()
{
        set_name("石塊", ({"stone"}));
        set_weight(60);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一塊小石子。\n");
                set("unit", "塊");
                set("value", 0);
        }
}
