#include <ansi.h>

inherit COMBINED_ITEM;
#include "meat.h"

void create()
{
        set_name(NOR + WHT "野豬肉" NOR, ({ "yezhu rou", "yezhu", "rou" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "這是一塊散發著腥臊臭的野豬肉。\n" NOR);
                set("base_unit", "塊");
                set("base_value", 50);
        }
        setup();
        set_amount(1);
}