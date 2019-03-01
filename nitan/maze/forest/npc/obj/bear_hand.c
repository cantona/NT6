#include <ansi.h>

inherit COMBINED_ITEM;
#include "/clone/quarry/item/meat.h"

void create()
{
        set_name("熊掌", ({ "bear hand" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "這是一塊散發著腥臊臭的熊肉。\n" NOR);
                set("base_unit", "塊");
                set("base_value", 80);
        }
        set("maze_item", 1);
        setup();
        set_amount(1);
}