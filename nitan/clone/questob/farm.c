// farm.c

inherit COMBINED_ITEM;

void create()
{
        set_name("農具", ({ "farm tool", "nong ju", "tool" }));
        if(clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "這是一副木製的農具。\n");
                set("base_unit", "副");
                set("base_weight", 8000);
                set("no_sell", 1);
                set("unit", "堆");
        }

        set_amount(1);
        setup();
}