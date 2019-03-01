// Room: /d/kunlun/obj/fish.c
// Last Modified by winder on Jun. 29 2001

inherit F_FOOD;
inherit ITEM;

void create()
{
        set_name("大白魚", ({ "fish" }) );
        set_weight(350);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一尾大白魚，長達一尺。\n");
                set("unit", "尾");
                set("value", 30);
                set("food_remaining", 4);
                set("food_supply", 40);
                set("material", "bone");
        }
        setup();
}

int finish_eat()
{
        set_name("魚骨", ({ "fish bone" }) );
        set_weight(150);
        set("long", "一根啃得精光的魚骨頭，看樣子可以作針。\n");
        return 1;
}