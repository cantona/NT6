// trans_cart.c
//

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("大車", ({ "cart" }));
        set_weight(200000);
        set_max_encumbrance(1000000);
        if (clonep())
        {
                set_default_object(__FILE__);
                call_out("destruct_me", 10);
        }
        else
        {
                set("value", 1);
                set("long", "這是一輛普通的馬車，行駛在大官道上，你覺得晃晃悠悠的。\n");
                set("unit", "輛");
                set("material", "wood");
                set("no_get", "好傢伙，車你也想扛在肩上？\n");
        }
        setup();
}

/*
void destruct_me()
{
        destruct(this_object());
}

*/