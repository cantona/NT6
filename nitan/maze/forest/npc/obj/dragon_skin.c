#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name("龍鱗", ({"dragon scale"}) );
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "龍鱗。\n" NOR);
                set("base_unit", "張");
                set("base_value", 20000);
                set("base_weight", 600);
        }
        set("maze_item", 1);
        setup();
        set_amount(1);
}