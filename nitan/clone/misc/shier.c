// shier.c 食餌

#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name("食餌", ({ "shi er", "shi", "er" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是獵人常用的誘餌。\n");
                set("base_unit", "塊");
                set("base_weight", 50);
                set("base_value", 10);
                set("no_sell", "幹啥？我又不打獵，要這些撈子做甚？");
                set("unit", "些");
        }
        set_amount(1);
        setup();
}