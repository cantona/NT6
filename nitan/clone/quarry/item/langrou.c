#include <ansi.h>

inherit COMBINED_ITEM;
#include "meat.h"

void create()
{
        set_name(NOR + WHT "狼肉" NOR, ({ "lang rou", "lang", "rou" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "這是一塊散發着腥臊臭的狼肉。\n" NOR);
                set("base_unit", "塊");
                set("base_value", 20);
        }
        setup();
        set_amount(1);
}