// fake-gold.c

inherit ITEM;

void create()
{
        set_name("黃金", ({"gold", "ingot", "gold_money"}));
        set_weight(150000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "黃澄澄的金子，人見人愛的金子，不過 ...顏色有點不對。\n");
                set("unit", "塊");
                set("material", "lead");
        }
        setup();
}
