#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(NOR + YEL "虎皮" NOR, ({ "hu pi", "hu", "pi" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + YEL "成年猛虎的皮，革質堅韌，皮毛"
                            "柔軟光滑之極。\n" NOR);
                set("base_unit", "張");
                set("base_value", 8000);
                set("base_weight", 500);
        }
        setup();
        set_amount(1);
}