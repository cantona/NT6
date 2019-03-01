// cloth.c

inherit COMBINED_ITEM;

void create()
{
        set_name("布料", ({ "cloth", "bu liao", "bu" }));
        if(clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "這是一匹絲織的布料。\n");
                set("base_unit", "匹");
                set("base_weight", 5000);
                set("no_sell", 1);
                set("unit", "堆");
        }

        set_amount(1);
        setup();
}