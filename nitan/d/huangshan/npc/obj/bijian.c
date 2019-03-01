// bijian.c

#include <weapon.h>
#include <ansi.h>
inherit SWORD;
void create()
{
        set_name( HIG "碧劍" NOR, ({ "green sword", "sword" }) );
        set_weight(7000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "這是一把翠綠色的劍，劍身又細又長。\n");
                set("value", 400);
                set("material", "steel");
        }
        init_sword(15);
        setup();
}