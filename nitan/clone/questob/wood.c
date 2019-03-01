// wood.c

inherit COMBINED_ITEM;

void create()
{
        set_name("木器", ({ "woodware", "mu qi", "wood" }));
        if(clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "這是一個木制的家具。\n");
                set("base_unit", "個");
                set("base_weight", 8000);
                set("no_sell", 1);
                set("unit", "些");
        }

        set_amount(1);
        setup();
}