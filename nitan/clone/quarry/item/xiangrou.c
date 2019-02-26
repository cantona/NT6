#include <ansi.h>

inherit COMBINED_ITEM;
#include "meat.h"

void create()
{
        set_name(NOR + WHT "象肉" NOR, ({ "xiang rou", "xiang", "rou" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "這是一塊散發着腥臊臭的象肉。\n" NOR);
                set("base_unit", "塊");
                set("base_value", 500);
        }
        setup();
        set_amount(1);
}