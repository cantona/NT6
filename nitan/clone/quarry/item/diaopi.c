#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(NOR + CYN "貂皮" NOR, ({ "diao pi", "diao", "pi" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + CYN "紫貂的皮毛，非常的名貴，相信"
                            "可以賣個好價錢，。\n" NOR);
                set("base_unit", "張");
                set("base_value", 10000);
                set("base_weight", 300);
        }
        setup();
        set_amount(1);
}