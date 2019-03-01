#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(NOR + WHT "狼皮" NOR, ({ "lang pi", "lang", "pi" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "狼的皮毛，毛雜不純，革質頗為粗糙。\n" NOR);
                set("base_unit", "張");
                set("base_value", 600);
                set("base_weight", 300);
        }
        set("maze_item", 1);
        setup();
        set_amount(1);
}