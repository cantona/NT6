#include <ansi.h>

inherit COMBINED_ITEM;
#include "meat.h"

void create()
{
        set_name(NOR + WHT "狍子肉" NOR, ({ "pao rou", "pao", "rou" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "這是一塊散發着腥臊臭的狍子肉。\n" NOR);
                set("base_unit", "塊");
                set("base_value", 40);
        }
        setup();
        set_amount(1);
}