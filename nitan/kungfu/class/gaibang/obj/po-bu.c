// po-bu.c
inherit ITEM;

void create()
{
        set_name("破布", ({"po bu", "piece"}));
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long","這是一塊破布，憑此可直接向簡長老要求升袋。\n");
                set("material", "cloth");
        }
}