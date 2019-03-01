// cloth: changpao.c
// Jay 3/17/96

#include <armor.h>
inherit CLOTH;

void create()
{
        set_name("波斯長袍", ({ "bosi robe", "robe"}));
        set("long", "這是一件臟兮兮的波斯長袍。\n");
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "件");
                set("value", 250);
                set("armor_prop/armor", 10);
        }
        setup();
}