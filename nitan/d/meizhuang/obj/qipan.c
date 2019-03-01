#include <weapon.h>
#include <ansi.h>

inherit HAMMER;

void create()
{
        set_name(CYN "鐵棋盤" NOR,({ "tie qipan", "tie", "qipan", "pan" }) );
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", CYN "一個用生鐵鑄成的棋盤，非常的重。\n" NOR);
                set("unit", "個");
                set("value", 3000);
                set("no_sell", 1);
                set("material", "steel");
                set("stable", 80);
        }
        init_hammer(40);
        setup();
}
