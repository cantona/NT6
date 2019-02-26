#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(NOR + WHT "狐狸皮" NOR, ({ "huli pi", "huli", "pi" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "這是一張毛質頗為不錯的狐狸皮。\n" NOR);
                set("base_unit", "張");
                set("base_value", 2000);
                set("base_weight", 300);
        }
        setup();
        set_amount(1);
}