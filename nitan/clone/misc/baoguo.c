#include <ansi.h>
inherit ITEM;

int is_bag() { return 1; }

void create()
{
        set_name(NOR + WHT "包裹" NOR, ({ "bag" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "這是一個包裹。\n");
                set("value", 0);
        }
        setup();
}