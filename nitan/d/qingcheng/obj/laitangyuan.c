// laitangyuan.c

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("賴湯圓", ({ "lai tangyuan", "tangyuan" }) );
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一碗香噴噴、甜絲絲的賴湯圓。\n");
                set("unit", "碗");
                set("value", 0);
                set("food_remaining", 5);
                set("food_supply", 30);
        }
}