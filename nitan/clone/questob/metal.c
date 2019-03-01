// metal.c

inherit COMBINED_ITEM;

void create()
{
        set_name("鐵器", ({ "metalware", "tie qi", "metal" }));
        if(clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "這是一把鐵制的家具。\n");
                set("base_unit", "把");
                set("base_weight", 15000);
                set("no_sell", 1);
                set("unit", "些");
        }

        set_amount(1);
        setup();
}