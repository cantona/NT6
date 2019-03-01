
#include <weapon.h>
#include <ansi.h>

inherit BLADE;

void create()
{
        set_name(HIY "絕命之刃" NOR, ({ "jueming zhiren",}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", HIY "這是一柄由天地靈氣聚集而成的鋒利之刃，似乎不應該屬于人間。\n" NOR);
                set("value", 1);
                set("material", "steel");
                set("wield_msg", "");
                set("unwield_msg", "");
        }
        init_blade(100);
        setup();
}

