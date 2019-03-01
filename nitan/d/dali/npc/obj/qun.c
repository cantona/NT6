// qun.c

#include <armor.h>
inherit CLOTH;

void create()
{
        set_name("白紗挑線鑲邊裙", ({ "xiangbian qun" }));
        set("long", "這是一件當地土著常用的白紗挑線鑲邊裙。\n");
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "件");
                set("value", 250);
                set("armor_prop/armor", 1);
        }
        setup();
}