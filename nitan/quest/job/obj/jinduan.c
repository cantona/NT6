// jinduan.c

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIY "錦緞" NOR, ({ "jinduan", "jin" }));
        set("long", "這是一件裝飾秀麗的錦緞。\n");
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "件");
                set("armor_prop/armor", 1);
                set("value", 1);
        }
        setup();
}
