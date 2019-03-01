// bait.c

inherit COMBINED_ITEM;

void create()
{
        set_name("魚餌", ({ "bait", "yu er", "er" }));
        if(clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "這是一袋新鮮的魚餌。\n");
                set("base_unit", "袋");
                set("base_weight", 4000);
                set("no_sell", 1);
                set("unit", "堆");
        }

        set_amount(1);
        setup();
}