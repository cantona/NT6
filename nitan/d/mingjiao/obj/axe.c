// Code of LXTX
// axe.c 斧頭

#include <weapon.h>
inherit AXE;

void create()
{
        set_name("斧頭", ({ "axe","fu" }));
        set_weight(9000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "這是一把斧頭，可以用來砍樹。\n");
                set("value", 10);
                set("material", "steel");
                set("no_drop",1);
        }
        init_axe(10);
        setup();
}
